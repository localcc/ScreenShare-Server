#include <network/UdpServer.h>

#include <network/packets/LoginPacket.h>
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
    LoginPacket loginPacket{.clientId = cStr};
    auto *packet = enet_packet_create(&loginPacket, sizeof(LoginPacket), 0);
    enet_peer_send(event.peer, 0, packet);

    this->clients.emplace(id,
                          std::make_unique<ConnectedClient>(
                                  id,
                                  std::unique_ptr<ENetPeer, decltype(&enet_peer_reset)>(
                                          event.peer,
                                          &enet_peer_reset)));
}

void UdpServer::HandlePacket(ENetEvent event) {
    const auto packetId = event.packet->data[0];
    std::cout << packetId << std::endl;
}


void UdpServer::HandleDisconnect(ENetEvent event) {
    auto id = reinterpret_cast<char*>(event.peer->data);
    if(id == nullptr) return;
    if(this->clients.erase(id) == 0) return;
    //todo: tell other clients about disconnect
}