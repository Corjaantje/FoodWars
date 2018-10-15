#include <include/enet/enet.h>
#include <SDL2/SDL_log.h>
#include <iostream>
#include "../../Headers/communication/Server.h"
#include "../../Headers/communication/IConnection.h"

IConnection::~IConnection() = default;

Server::Server(const std::string &ip, const int port) : server(nullptr)  {
    if(!connect(ip, port)){
        throw "An error occurred while trying to create an ENet server host.";
    }
}

bool Server::connect(std::string ip, int port) {
    if(server != nullptr)
        close();

    //create the address for the server
    ENetAddress address;
    enet_address_set_host (&address, &ip[0]);
    address.port = (enet_uint16) port;
    std::cout << "Server address: " << address.host << ":" << address.port << std::endl;

    //Creates a host for communicating to peers
    server = enet_host_create (& address /* the address to bind the server host to */,
                               32      /* allow up to 32 clients and/or outgoing connections */,
                               2      /* allow up to 2 channels to be used, 0 and 1 */,
                               0      /* assume any amount of incoming bandwidth */,
                               0      /* assume any amount of outgoing bandwidth */);

    return server != nullptr;
}

//listen for the specified amount of time for incomming connections and other events
bool Server::listen(const int timeout)  {
    ENetEvent event;
    int eventStatus = enet_host_service (server, &event, (enet_uint32) timeout);
    if (eventStatus > 0) {
        std::cout << "Recieved event. Status: " << eventStatus << " type: " << event.type << std::endl;
        switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                printf("(Server) We got a new connection from %x\n",
                       event.peer->address.host);
                break;

            case ENET_EVENT_TYPE_RECEIVE:
                printf("(Server) Message from client : %s\n", event.packet->data);
                // Lets broadcast this message to all clients
                enet_host_broadcast(server, 0, event.packet);
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                printf("%s disconnected.\n", event.peer->data);
                // Reset client's information
                event.peer->data = nullptr;
                break;
            case ENET_EVENT_TYPE_NONE:break;
        }
    }
    return eventStatus > 0;
}

void Server::handleUpdate() {
    listen(10);
}

Server::~Server() {
    enet_host_destroy(server);
    delete server;
}

bool Server::close() {
    enet_host_destroy(server);
    delete server;
    return true;
}

bool Server::hasPendingUpdates() {
    listen(0);
    return false;
}

bool Server::sendPacket(Packet packet) {
    ENetPacket* eNetPacket = enet_packet_create(
            &packet.getContent()[0],
            packet.getContent().length() + 1,
            ENET_PACKET_FLAG_RELIABLE
    );
    //send packet to all connected clients
    enet_host_broadcast(server, 0, eNetPacket);
    return true;
}
