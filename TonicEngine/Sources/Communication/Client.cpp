#include <include/enet/enet.h>
#include <SDL2/SDL_log.h>
#include "../../Headers/communication/Client.h"
#include "../../Headers/communication/IConnection.h"

Client::Client(const std::string &ip, const int port): client(nullptr), peer(nullptr) {
    if(!connect(ip, port)) {
        throw "An error occurred while trying to create the client.";
    }
}

bool Client::close() {
    if(peer != nullptr) {
        enet_peer_disconnect(peer, 0);
    }
    if(client != nullptr) {
        ENetEvent event;
        /* Allow up to 3 seconds for the disconnect to succeed
         * and drop any packets received packets. */
        while (enet_host_service(client, &event, 3000) > 0) {
            switch (event.type) {
                case ENET_EVENT_TYPE_RECEIVE:
                    enet_packet_destroy(event.packet);
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    puts("Disconnection succeeded.");
                    return true;
                case ENET_EVENT_TYPE_NONE:
                    break;
                case ENET_EVENT_TYPE_CONNECT:
                    break;
            }
        }
        if(peer != nullptr)
            enet_peer_reset(peer);
        enet_host_destroy(client);
    }
    return true;
}

bool Client::connect(std::string ip, int port) {
    if(client != nullptr) {
        close();
    }
    //Creates a host for communicating to peers
    client = enet_host_create (nullptr /* create a client host */,
                               1 /* only allow 1 outgoing connection */,
                               2 /* allow up 2 channels to be used, 0 and 1 */,
                               0 /* assume any amount of incoming bandwidth */,
                               0 /* assume any amount of incoming bandwidth */);
    ENetAddress address;
    enet_address_set_host (&address, &ip[0]);
    address.port = (enet_uint16) port;
    if(client != nullptr){
        peer = enet_host_connect (client, &address, 2, 0);
        return peer != nullptr;
    }
    return false;
}

Client::~Client() {
    ENetEvent event;
    enet_peer_disconnect(peer, 0);
    /* Allow up to 3 seconds for the disconnect to succeed
     * and drop any packets received packets. */
    while (enet_host_service(client, &event, 3000) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE:
                enet_packet_destroy(event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                return;
            case ENET_EVENT_TYPE_NONE:
                break;
            case ENET_EVENT_TYPE_CONNECT:
                break;
        }
    }
    enet_peer_reset(peer);
    enet_host_destroy(client);
    delete(client);
}

bool Client::connectToHost(const int timeout) {
    ENetEvent event;

    //Connect to the host and check if we received an connect event
    int eventStatus = enet_host_service(client, &event, (enet_uint32) timeout);
    if (eventStatus > 0) {
        if (event.type == ENET_EVENT_TYPE_CONNECT) {
            return true;
            //return true;
        }
    } else {
        enet_peer_reset(peer);
    }

    return false;
}

bool Client::sendPacket(Packet packet) {
    // convert our packet to an ENetPacket
    ENetPacket* eNetPacket = enet_packet_create(
            &packet.getContent()[0],
            packet.getContent().length() + 1,
            ENET_PACKET_FLAG_RELIABLE
    );

    enet_peer_send(peer, 0, eNetPacket);
    ENetEvent event;
    // cal enet host service so the packet will be send
    enet_host_service(client, &event, 0);
    //enet_host_service should be called very regularly, The best way to schedule this activity to ensure adequate service is, for example, to call enet_host_service() with a 0 timeout (meaning non-blocking) at the beginning of every frame in a game loop.
    return true;
}

bool Client::hasPendingUpdates() {
    return enet_host_service(client, nullptr, 0) > 0;
}

void Client::handleUpdate() {

}

