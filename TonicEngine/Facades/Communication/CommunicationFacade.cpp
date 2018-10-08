#include "../../Headers/Communication/CommunicationFacade.h"

/**
 The facade to communicate to someone across a network. This facade is a quick setup with which a client and server can be created.
 When we are going to use multiplayer this facade will have to be adjusted very much.
 */
CommunicationFacade::CommunicationFacade() = default;

CommunicationFacade::~CommunicationFacade() = default;

IConnection* CommunicationFacade::createClient(const std::string ip, const int port) {
    return new Client(ip, port);
}

IConnection* CommunicationFacade::createServer(const std::string ip, const int port) {
    return new Server(ip, port);
}

Packet CommunicationFacade::createPacket(std::string content) {
    return Packet(content);
}

