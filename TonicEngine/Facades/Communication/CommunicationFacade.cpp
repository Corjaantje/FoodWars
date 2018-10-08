#include "../../Headers/Communication/CommunicationFacade.h"

/**
 De facade om te communiceren met een ander over een netwerk. Deze facade is een snelle opzet waarmee een client en server kunnen worden aangemaakt.
 Wanneer we echt multiplayer gaan gebruiken zal de facade nog heel erg aangepast moeten worden.
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

