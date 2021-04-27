#pragma once
#include <network/packets/PacketIds.h>
#include <cstdint>

#if defined(__GNUC__) || defined(__llvm__) || defined(__clang__)
struct __attribute__((packed)) LoginPacket {
#elif defined(WIN32)
#pragma pack(push, 1)
struct LoginPacket {
#endif
    uint8_t packetId = LOGIN_PACKET_ID;
    const char* clientId;
};
#if defined(WIN32)
#pragma pack(pop)
#endif