#include <include/enet/enet.h>
#include <SDL2/SDL_log.h>
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

    ENetAddress address;
    /* Bind the server to the default localhost.     */
    /* A specific host address can be specified by   */
    /* enet_address_set_host (& address, "x.x.x.x"); */
    enet_address_set_host (&address, &ip[0]);
    /* Bind the server to port 1234. */
    address.port = (enet_uint16) port;
    //std::cout << "Server address: " << address.host << ":" << address.port << std::endl;
    server = enet_host_create (& address /* the address to bind the server host to */,
                               32      /* allow up to 32 clients and/or outgoing connections */,
                               2      /* allow up to 2 channels to be used, 0 and 1 */,
                               0      /* assume any amount of incoming bandwidth */,
                               0      /* assume any amount of outgoing bandwidth */);

    return server != nullptr;
}

bool Server::listen(const int timeout)  {
    ENetEvent event;
    int eventStatus = enet_host_service (server, &event, (enet_uint32) timeout);
    if (eventStatus > 0) {
        SDL_Log("Event recieved.");
        //std::cout << "Recieved event. Status: " << eventStatus << " type: " << event.type << std::endl;
        switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                printf("(Server) We got a new connection from %x\n",
                       event.peer->address.host);
                SDL_Log("(Server) We got a new connection from %x\n",
                        event.peer->address.host);
                //connectedPeers.push_back(*event.peer);
                break;

            case ENET_EVENT_TYPE_RECEIVE:
                printf("(Server) Message from client : %s\n", event.packet->data);
                SDL_Log("(Server) Message from client : %s\n", event.packet->data);
                // Lets broadcast this message to all
                enet_host_broadcast(server, 0, event.packet);
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                printf("%s disconnected.\n", event.peer->data);
                //connectedPeers.erase(std::remove(connectedPeers.begin(), connectedPeers.end(), event.peer));
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
    /*for(ENetPeer peer: connectedPeers) {
        ENetEvent event;
        enet_peer_disconnect(&peer, 0);
        *//* Allow up to 3 seconds for the disconnect to succeed
         * and drop any packets received packets. *//*
        while (enet_host_service(server, &event, 3000) > 0) {
            switch (event.type) {
                case ENET_EVENT_TYPE_RECEIVE:
                    enet_packet_destroy(event.packet);
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    puts("Disconnection succeeded.");
                    return;
                case ENET_EVENT_TYPE_NONE:
                    break;
                case ENET_EVENT_TYPE_CONNECT:
                    break;
            }
        }
        enet_peer_reset(&peer);
    }*/
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
    /*for (ENetPeer peer: connectedPeers) {
        enet_peer_send(&peer, 0, eNetPacket);
    }*/
    enet_host_broadcast(server, 0, eNetPacket);
    return true;
}
