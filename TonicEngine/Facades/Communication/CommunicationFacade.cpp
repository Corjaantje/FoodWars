#include "../../Headers/Communication/CommunicationFacade.h"

/**
 The facade to communicate to someone across a network. This facade is a quick setup with which a client and server can be created.
 When we are going to use multiplayer this facade will have to be adjusted very much.
 */
CommunicationFacade::CommunicationFacade() = default;

CommunicationFacade::~CommunicationFacade() = default;

std::unique_ptr<IConnection> CommunicationFacade::createClient(std::string ip, int port) {
    return std::unique_ptr<IConnection>(new Client(ip, port));
}

std::unique_ptr<IConnection> CommunicationFacade::createServer(std::string ip, int port) {
    return std::unique_ptr<IConnection>(new Server(ip, port));
}

Packet CommunicationFacade::createPacket(std::string content) {
    return Packet(content);
}

