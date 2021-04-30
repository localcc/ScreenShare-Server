#include <network/ConnectedClient.h>
#include <proto/ClientDisconnected.pb.h>
#include <network/PacketIds.h>

ConnectedClient::ConnectedClient(std::string &id, std::unique_ptr<ENetPeer, decltype(&enet_peer_reset)> peer) :
        id(id), peer(std::move(peer)) {
}

const std::string ConnectedClient::getId() const {
    return this->id;
}

int32_t ConnectedClient::send(ENetPacket *packet, int32_t channel) {
    return enet_peer_send(this->peer.get(), channel, packet);
}

void ConnectedClient::addWatchedByMe(const std::string &id) {
    this->watchedByMe.push_back(id);
}

void ConnectedClient::addWatchingMe(const std::string &id) {
    this->watchingMe.push_back(id);
}

void ConnectedClient::removeWatchedByMe(const std::string &id) {
    std::remove(this->watchedByMe.begin(), this->watchedByMe.end(), id);
}

void ConnectedClient::removeWatchingMe(const std::string &id) {
    std::remove(this->watchingMe.begin(), this->watchingMe.end(), id);
}

std::vector<std::string> ConnectedClient::getWatchedByMe() const {
    return this->watchedByMe;
}

std::vector<std::string> ConnectedClient::getWatchingMe() const {
    return this->watchingMe;
}

void ConnectedClient::startStreaming() {
    this->streaming = true;
}

void ConnectedClient::stopStreaming() {
    this->streaming = false;
}

[[nodiscard]] bool ConnectedClient::getStreaming() const {
    return this->streaming;
}

void ConnectedClient::notifyDisconnect(const std::string &id) {
    auto* disconnectProto = new network::packets::ClientDisconnected();
    disconnectProto->set_id(id);

    const auto size = disconnectProto->ByteSizeLong();
    uint8_t* data = new uint8_t[size + 1];
    data[0] = PacketIds::ClientDisconnected;
    disconnectProto->SerializeToArray(data + 1, size);

    ENetPacket* packet = enet_packet_create(data, size + 1, 0);
    enet_peer_send(this->peer.get(), 0, packet);

    delete disconnectProto;
    delete[] data;
}
