cmake_minimum_required(VERSION 3.19)
project(ScreenShare_Server)

set(LIBS_DIR ${CMAKE_SOURCE_DIR}/libs)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(${LIBS_DIR})

file(GLOB PACKETS_SRC ${CMAKE_SOURCE_DIR}/include/network/packets/"*.h")

add_executable(ScreenShare_Server main.cpp include/network/UdpServer.h src/network/UdpServer.cpp
        include/network/EnetHelper.h include/network/ConnectedClient.h src/network/ConnectedClient.cpp ${PACKETS_SRC} include/network/packets/LoginPacket.h include/network/packets/PacketIds.h)
include_directories(${LIBS_DIR}/enet/include ${CMAKE_SOURCE_DIR}/include)