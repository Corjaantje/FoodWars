#include "../Headers/InputSystem.h"
#include <iostream>
#include <SDL2/SDL_render.h>

InputSystem::InputSystem(int width, int height, int x, int y) :
_width(width), _height(height), _x(x), _y(y)
{
    SDL_Window *win = SDL_CreateWindow("Rendering to a texture!", SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    _renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
}

void InputSystem::draw() const {
    SDL_Rect rect;

    rect.w = _width;
    rect.h = _height;
    rect.x = _x;
    rect.y = _y;

    SDL_SetRenderDrawColor(_renderer, 200, 20, 200, 255);
    SDL_RenderFillRect(_renderer, &rect);

    SDL_RenderPresent(_renderer);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 200, 255);
    SDL_RenderClear(_renderer);
}

void InputSystem::pollEvents() {
    SDL_Event event;

    if(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                _closed = true;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        _closed = true;
                        break;
                    case SDLK_LEFT:
                        _x -= 10;
                        break;
                    case SDLK_RIGHT:
                        _x += 10;
                        break;
                    case SDLK_UP:
                        _y -= 10;
                        break;
                    case SDLK_DOWN:
                        _y += 10;
                        break;
                }
            default:
                break;
        }
    }
}