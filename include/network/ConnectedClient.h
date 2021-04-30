#pragma once
#include <string>
#include <memory>
#include <enet.h>
#include <cstdint>
#include <vector>

class ConnectedClient {
public:
    ConnectedClient(std::string& id, std::unique_ptr<ENetPeer, decltype(&enet_peer_reset)> peer);

    [[nodiscard]] const std::string getId() const;

    int32_t send(ENetPacket* packet, int32_t channel);

    void startStreaming();
    void stopStreaming();
    [[nodiscard]] bool getStreaming() const;

    void addWatchedByMe(const std::string& id);
    void removeWatchedByMe(const std::string& id);

    void addWatchingMe(const std::string& id);
    void removeWatchingMe(const std::string& id);

    [[nodiscard]] std::vector<std::string> getWatchedByMe() const;
    [[nodiscard]] std::vector<std::string> getWatchingMe() const;

    ~ConnectedClient() = default;
private:
    std::string id;

    bool streaming;
    std::vector<std::string> watchedByMe;
    std::vector<std::string> watchingMe;

    std::unique_ptr<ENetPeer, decltype(&enet_peer_reset)> peer;
};