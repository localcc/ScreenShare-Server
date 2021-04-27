#define ENET_IMPLEMENTATION
#include <enet.h>
#include <iostream>
#include <random>
#include <network/UdpServer.h>
#include <sstream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if(argc != 3) {
        std::cout << "Invalid arguments!" << std::endl;
        std::cout << "Usage: [HOST] [PORT]" << std::endl;
        return -2;
    }


    if(enet_initialize() != 0) {
        std::cout << "Failed to initialize network! Aborting" << std::endl;
        return -3;
    }

    std::string host(argv[1]);
    char* endPtr;
    uint16_t port = strtol(argv[2], &endPtr, 10);
    if(endPtr == argv[2] || errno == ERANGE) {
        std::cout << "Failed to parse port number! Aborting!" << std::endl;
        return -4;
    }


    static std::random_device              rand;
    static std::mt19937                    gen(rand());
    static std::uniform_int_distribution<> dist(0, 15);

    UdpServer server(host, port, 32, 0, 0, [&](){
        std::stringstream id;
        id << std::hex;
        for(uint8_t i = 0; i < 64; i++) {
            id << dist(gen);
        }
        return id.str();
    });
    server.Start();
    return 0;
}
