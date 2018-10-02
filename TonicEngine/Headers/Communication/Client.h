//
// Created by Lucas on 30/09/2018.
//

#ifndef PROJECT_SWA_ICLIENT_H
#define PROJECT_SWA_ICLIENT_H

#include "Server.h"
#include "IConnection.h"
#include <include/enet/enet.h>

class Client : public IConnection {
private:
    ENetAddress address;
    ENetHost* client;
    ENetPeer* peer;
public:
    Client(const std::string &ip, int port);
    ~Client();
    bool sendPacket(Packet packet) override;
    bool connectToHost(int timeout);

    bool connect(std::string ip, int port) override;

    bool close() override;

    bool hasPendingUpdates() override;
    void handleUpdate() override;
};
#endif //PROJECT_SWA_ICLIENT_H
