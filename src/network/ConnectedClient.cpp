#include <network/ConnectedClient.h>

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