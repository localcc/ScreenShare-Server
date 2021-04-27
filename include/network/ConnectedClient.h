#pragma once
#include <string>
#include <memory>
#include <enet.h>
#include <cstdint>

class ConnectedClient {
public:
    ConnectedClient(std::string& id, std::unique_ptr<ENetPeer, decltype(&enet_peer_reset)> peer);

    ~ConnectedClient() = default;
private:
    std::string id;
    std::unique_ptr<ENetPeer, decltype(&enet_peer_reset)> peer;
};