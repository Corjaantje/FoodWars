#ifndef PROJECT_SWA_ISERVER_H
#define PROJECT_SWA_ISERVER_H

#include <string>
#include "Packet.h"
#include "IConnection.h"
#include <include/enet/enet.h>

class Server: public IConnection {
private:
    ENetHost* server;
public:
    Server(const std::string &ip, int port);
    ~Server() override;
    bool listen(int timeout);

    bool connect(std::string ip, int port) override;

    bool close() override;

    bool hasPendingUpdates() override;

    bool sendPacket(Packet packet) override;

    void handleUpdate() override;
};
#endif //PROJECT_SWA_ISERVER_H
