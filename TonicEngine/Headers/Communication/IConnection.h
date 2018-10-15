//
// Created by Lucas on 01/10/2018.
//

#ifndef PROJECT_SWA_ICONNECTION_H
#define PROJECT_SWA_ICONNECTION_H

#include <string>
#include "Packet.h"

class IConnection {
public:
    IConnection() = default;
    virtual ~IConnection() = 0;
    virtual bool connect(std::string ip, int port) = 0;
    virtual bool close() = 0;
    virtual bool hasPendingUpdates() = 0;
    virtual void handleUpdate() = 0;
    virtual bool sendPacket(Packet packet) = 0;
};
#endif //PROJECT_SWA_ICONNECTION_H
