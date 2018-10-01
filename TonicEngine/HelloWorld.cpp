#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <include/enet/enet.h>
#include "Headers/communication/CommunicationFacade.h"

int main(int argc, char** argv)
{
    if (enet_initialize() != 0)
    {
        fprintf (stderr, "An error occurred while initializing ENet.\n");
        return EXIT_FAILURE;
    }
    atexit (enet_deinitialize);

    SDL_Window *win = SDL_CreateWindow("Rendering to a texture!", SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED, 640, 480, 0);

    std::string ip = "145.49.108.110";
    int port = 1234;
    std::string input;

    CommunicationFacade communicationFacade;
    IConnection* connection = nullptr;

    SDL_Log("Please type 'h' for Host or 'c' for Client");
    bool isRunning = true;
    bool hasConnection = false;
    SDL_Event event;
    while(isRunning) {
        if(hasConnection) {
            bool hasUpdates = connection->hasPendingUpdates();
            if(hasUpdates)
                connection->handleUpdate();
            //SDL_Log(hasUpdates ? "true" : "false");
        }
        while(SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_QUIT)
                isRunning = false;
            else if(event.type == SDL_TEXTINPUT){
                switch(*event.text.text){
                    case 'q':
                        isRunning = false;
                        break;
                    case 'c':
                        if(!hasConnection){
                            SDL_Log("Creating client...");
                            connection = communicationFacade.createClient(ip, port);
                            hasConnection = true;
                        }
                        break;
                    case 'h':
                        if(!hasConnection){
                            SDL_Log("Creating server...");
                            connection = communicationFacade.createServer(ip, port);
                            (dynamic_cast<Server*>(connection))->listen(10000);
                            hasConnection = true;
                        }
                    case 'p':
                        if(hasConnection) {
                            connection->sendPacket(communicationFacade.createPacket("Hello!"));
                        }
                    default:break;
                }
                //input += event.text.text;
            }
        }
        SDL_UpdateWindowSurface(win);
    }

    delete connection;

    /*std::string segment;
    std::string ip = input.substr(2, input.length() - 3);
    SDL_Log(&input[0]);
    if(input[0] == 'c') {
        SDL_Log("Creating client..");
        Client client(ip, 1234);
        SDL_Log("Connecting to ");
        SDL_Log(ip.c_str());
        while (!client.connectToHost(1000)){
            SDL_Log("Update");
            SDL_PollEvent(&event);
            SDL_UpdateWindowSurface(win);
        }
        SDL_Log("Sending packet to server");
        client.sendPacket(Packet("Hello from client"));
    } else {
        SDL_Log("Creating server..");
        SDL_Log(&ip[0]);
        Server server(ip, 1234);
        SDL_Log("Start listening.");
        while(!server.listen(1000)){
            SDL_PollEvent(&event);
            SDL_UpdateWindowSurface(win);
        }
    }*/

    win = nullptr;
    SDL_Quit();
    // When the world destructor is called, all bodies and joints are freed. This can
    // create orphaned pointers, so be careful about your world management.

    return 0;
}
