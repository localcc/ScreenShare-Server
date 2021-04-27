#include <network/ConnectedClient.h>

ConnectedClient::ConnectedClient(std::string &id, std::unique_ptr<ENetPeer, decltype(&enet_peer_reset)> peer) :
        id(id), peer(std::move(peer)) {

}