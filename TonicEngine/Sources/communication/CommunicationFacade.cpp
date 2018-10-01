#include "../../Headers/communication/CommunicationFacade.h"

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

