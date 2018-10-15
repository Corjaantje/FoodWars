//
// Created by Lucas on 30/09/2018.
//

#ifndef PROJECT_SWA_COMMUNICATIONFACADE_H
#define PROJECT_SWA_COMMUNICATIONFACADE_H

#include <bits/unique_ptr.h>
#include "Client.h"
#include "Server.h"
#include "Packet.h"

class CommunicationFacade {
public:
    CommunicationFacade();
    ~CommunicationFacade();
    std::unique_ptr<IConnection> createClient(std::string ip, int port);
    std::unique_ptr<IConnection> createServer(std::string ip, int port);
    Packet createPacket(std::string content);
    void update();
};

#endif //PROJECT_SWA_COMMUNICATIONFACADE_H
