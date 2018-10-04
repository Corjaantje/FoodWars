#include "../../Headers/Input/InputSystem.h"
#include "../../Headers/Input/InputObservable.h"
#include <iostream>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

InputSystem::InputSystem(const int &width, const int &height, const int &x, const int &y) :
        _width(width), _height(height), _x(x), _y(y)
{
    createWindow();
    initializeRectangle();
    draw();

    // Register as observer on the observable
    InputObservable observable(*this);

    // Loop goes on until escape is pressed or you exit the program
    while(!observable.isClosed()) {
        observable.pollEvents(_rect);
    }
}

void InputSystem::createWindow() {
    _win = SDL_CreateWindow("Rendering to a texture!", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    _renderer = SDL_CreateRenderer(_win, -1, SDL_RENDERER_ACCELERATED);
}

// Initializes the width, height, x and y position on our rectangle
void InputSystem::initializeRectangle() {
    _rect.w = _width;
    _rect.h = _height;
    _rect.x = _x;
    _rect.y = _y;
}

void InputSystem::draw() const {

    // Draws the background
    SDL_SetRenderDrawColor(_renderer, 0, 0, 200, 255);
    SDL_RenderClear(_renderer);

    // Draws the rectangle
    SDL_SetRenderDrawColor(_renderer, 200, 20, 200, 255);
    SDL_RenderFillRect(_renderer, &_rect);
    SDL_RenderPresent(_renderer);
}

// Initializes our rectangle with the updated rectangle from the observable and redraws everything
void InputSystem::update(const SDL_Rect &rect) {
    _rect = rect;
    draw();
}
