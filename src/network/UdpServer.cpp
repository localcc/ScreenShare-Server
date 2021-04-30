#include <network/UdpServer.h>
#include <proto/Login.pb.h>
#include <network/PacketIds.h>
#include <proto/ClientsInfo.pb.h>
#include <proto/StartWatching.pb.h>
#include <proto/StopWatching.pb.h>
#include <iostream>

UdpServer::UdpServer(std::string &host, uint16_t port, int32_t maxConnections, int32_t maxIn, int32_t maxOut, std::function<std::string()> genId) :
    genId(genId),
    host(EnetHelper::CreateServer(host, port, maxConnections, 2, maxIn, maxOut)),
    clients(),
    running(false){

}

void UdpServer::Start() {
    this->running = true;
    this->Run();
}

void UdpServer::Run() {
    ENetEvent event;
    while(this->running && enet_host_service(this->host.get(), &event, 0) >= 0) {
        switch(event.type) {
            case ENET_EVENT_TYPE_CONNECT: {
                this->HandleLogin(event);
                break;
            }
            case ENET_EVENT_TYPE_RECEIVE: {
                this->HandlePacket(event);
                enet_packet_destroy(event.packet);
                break;
            }
            case ENET_EVENT_TYPE_DISCONNECT: {
                this->HandleDisconnect(event);
                break;
            }
            case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT: {
                this->HandleDisconnect(event);
                break;
            }
            case ENET_EVENT_TYPE_NONE:
                break;
        }
    }
}

void UdpServer::HandleLogin(ENetEvent event) {
    auto id = this->genId();
    const auto cStr = id.c_str();
    event.peer->data = reinterpret_cast<void *>(const_cast<char *>(cStr));

    auto* loginPacket = new network::packets::Login();
    loginPacket->set_userid(id);
    const auto size = loginPacket->ByteSizeLong();

    auto* bytes = new uint8_t[size];
    loginPacket->SerializeToArray(bytes, size);

    auto *packet = enet_packet_create(bytes, size, 0);
    enet_peer_send(event.peer, 0, packet);

    this->clients.emplace(id,
                          std::make_unique<ConnectedClient>(
                                  id,
                                  std::unique_ptr<ENetPeer, decltype(&enet_peer_reset)>(
                                          event.peer,
                                          &enet_peer_reset)));
}

void UdpServer::HandlePacket(ENetEvent event) {
    const auto packetId = static_cast<PacketIds>(event.packet->data[0]);
    switch(packetId) {
        case GetClients: {
            auto clientsInfo = new network::packets::ClientsInfo();
            for (const auto &client : this->clients)  {
                auto clientInfo = clientsInfo->add_clients();
                clientInfo->set_id(client.second->getId());
                clientInfo->set_streaming(client.second->getStreaming());
            }
            const auto size = clientsInfo->ByteSizeLong();
            uint8_t* data = new uint8_t[size];
            clientsInfo->SerializeToArray(data, size);

            ENetPacket* packet = enet_packet_create(data, size, 0);
            enet_peer_send(event.peer, 0, packet);
            break;
        }
        case StartWatching: {
            if(event.peer->data == nullptr) {
                std::cerr << "Unauthenticated client tried to send a packet, dropping" << std::endl;
                break;
            }
            if(event.packet->dataLength <= 2) break;
            auto watchingProto = network::packets::StartWatching();
            if(!watchingProto.ParseFromArray(event.packet->data + 1, event.packet->dataLength - 1)) {
                std::cerr << "Failed to parse StartWatching packet for clientId: " << reinterpret_cast<char*>(event.peer->data) << std::endl;
                break;
            }

            const auto issuerId = std::string(reinterpret_cast<char*>(event.peer->data));
            const auto watchedId = watchingProto.id();

            auto srcFind = this->clients.find(issuerId);
            if(srcFind == this->clients.end()) break;
            auto dstFind = this->clients.find(watchedId);
            if(dstFind == this->clients.end()) break;
            if(!dstFind->second->getStreaming()) {
                std::cerr << "Client " << issuerId << " tried to watch stream of a client " << watchedId << " that is not streaming" << std::endl;
                break;
            }
            srcFind->second->addWatchedByMe(watchedId);
            dstFind->second->addWatchingMe(issuerId);

            break;
        }
        case StopWatching: {
            if(event.peer->data == nullptr) {
                std::cerr << "Unauthenticated client tried to send a packet, dropping" << std::endl;
                break;
            }
            if(event.packet->dataLength <= 2) break;
            auto watchingProto = network::packets::StopWatching();
            if(!watchingProto.ParseFromArray(event.packet->data + 1, event.packet->dataLength - 1)) {
                std::cerr << "Failed to parse StopWatching packet for clientId: " << reinterpret_cast<char*>(event.peer->data) << std::endl;
                break;
            }

            const auto issuerId = std::string(reinterpret_cast<char*>(event.peer->data));
            const auto watchedId = watchingProto.id();

            auto srcFind = this->clients.find(issuerId);
            if(srcFind == this->clients.end()) {
                srcFind->second->removeWatchedByMe(watchedId);
            }
            auto dstFind = this->clients.find(watchedId);
            if(dstFind != this->clients.end()) {
                dstFind->second->removeWatchingMe(issuerId);
            }

            break;
        }
        case StartStreaming: {
            if(event.peer->data == nullptr) break;

            const auto search = this->clients.find(reinterpret_cast<char*>(event.peer->data));
            if(search == this->clients.end()) {
                std::cerr << "Unauthenticated client tried to send a packet, dropping" << std::endl;
                break;
            }

            search->second->startStreaming();
            break;
        }
        case StopStreaming: {
            if(event.peer->data == nullptr) break;

            const auto issuerId = std::string(reinterpret_cast<char*>(event.peer->data));
            const auto search = this->clients.find(issuerId);
            if(search == this->clients.end()) {
                std::cerr << "Unauthenticated client tried to send a packet, dropping" << std::endl;
                break;
            }

            search->second->stopStreaming();
            const auto watching = search->second->getWatchingMe();
            for(const auto& watchingClientId : watching) {
                const auto watchingClient = this->clients.find(watchingClientId);
                if(watchingClient == this->clients.end()) continue;
                watchingClient->second->removeWatchedByMe(issuerId);
                search->second->removeWatchingMe(watchingClientId);
            }
            break;
        }
    }
    std::cout << "Packet id: " << static_cast<int32_t>(packetId) << std::endl;
}


void UdpServer::HandleDisconnect(ENetEvent event) {
    auto id = reinterpret_cast<char*>(event.peer->data);
    if(id == nullptr) return;
    if(this->clients.erase(id) == 0) return;
    //todo: tell other clients about disconnect
}