//
// Created by svanr on 10/1/2018.
//

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

#ifndef PROJECT_SWA_INPUTSYSTEM_H
#define PROJECT_SWA_INPUTSYSTEM_H

class InputSystem {
public:
    SDL_Rect _rect;

    InputSystem(const int &width, const int &height, const int &x, const int &y);
    void createWindow();
    void initializeRectangle();
    void draw() const;
    void update(const SDL_Rect &rect);
private:
    int _width, _height;
    int _x, _y;

    SDL_Renderer *_renderer = nullptr;
    SDL_Window *_win = nullptr;
};

#endif //PROJECT_SWA_INPUTSYSTEM_H