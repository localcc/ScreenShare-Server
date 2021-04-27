#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <network/EnetHelper.h>
#include <network/ConnectedClient.h>
#include <thread>
#include <map>
#include <functional>
#include <enet.h>

class UdpServer {
public:
    UdpServer(std::string& host, uint16_t port, int32_t maxConnections, int32_t maxIn, int32_t maxOut, std::function<std::string()> genId);

    void Start();

    ~UdpServer() = default;

private:

    void HandleLogin(ENetEvent event);
    void HandlePacket(ENetEvent event);
    void HandleDisconnect(ENetEvent event);

    void Run();


    std::function<std::string()> genId;
    std::unique_ptr<ENetHost, decltype(&enet_host_destroy)> host;
    std::map<std::string, std::unique_ptr<ConnectedClient>> clients;
    bool running;
};