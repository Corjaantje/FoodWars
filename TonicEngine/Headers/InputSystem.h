//
// Created by svanr on 9/30/2018.
//

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>

#ifndef PROJECT_SWA_INPUTSYSTEM_H
#define PROJECT_SWA_INPUTSYSTEM_H

#endif //PROJECT_SWA_INPUTSYSTEM_H

class InputSystem
{
public:
    InputSystem(int width, int height, int x, int y);

    void draw() const;
    void pollEvents();

    inline bool isClosed() const { return _closed; }
private:
    bool _closed = false;
    int _width, _height;
    int _x, _y;
    SDL_Renderer *_renderer = nullptr;
};
