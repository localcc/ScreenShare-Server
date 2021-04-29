cmake_minimum_required(VERSION 3.19)
project(ScreenShare_Server)

set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(PROTO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/proto)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(${LIBS_DIR})

find_package(Protobuf REQUIRED)

file(GLOB PROTO_FILES ${PROTO_PATH}/*.proto)
add_executable(ScreenShare_Server main.cpp include/network/UdpServer.h src/network/UdpServer.cpp
        include/network/EnetHelper.h include/network/ConnectedClient.h src/network/ConnectedClient.cpp)
foreach(proto ${PROTO_FILES})
    target_sources(ScreenShare_Server PRIVATE ${proto})
endforeach(proto)

include_directories(${LIBS_DIR}/enet/include ${CMAKE_CURRENT_SOURCE_DIR}/include)

protobuf_generate(TARGET ScreenShare_Server PROTOC_OUT_DIR ${PROTO_PATH} EXPORT_MACRO FALSE)
include_directories(${PROTO_PATH})
target_link_libraries(ScreenShare_Server protobuf::libprotobuf)