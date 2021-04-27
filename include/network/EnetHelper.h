#pragma once
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <enet.h>


class EnetHelper {
public:
    static std::unique_ptr<ENetHost, decltype(&enet_host_destroy)> CreateServer(std::string& host, uint16_t port, int32_t maxConnections, int32_t channels, int32_t maxIn = 0, int32_t maxOut = 0) {
        ENetAddress address{.port = port};
        if(!host.empty()) {
            enet_address_set_host(&address, host.c_str());
        }

        ENetHost* server = enet_host_create(&address, maxConnections, channels, maxIn, maxOut);
        if(server == nullptr) {
            throw std::runtime_error("Failed to create network host!");
        }
        return std::unique_ptr<ENetHost, decltype(&enet_host_destroy)>(server, &enet_host_destroy);
    }
};