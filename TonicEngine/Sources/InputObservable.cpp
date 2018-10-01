#include <list>
#include <SDL2/SDL_events.h>
#include "../Headers/InputObservable.h"

// Registers the observer
InputObservable::InputObservable(InputSystem observer) :
    _observer(observer) { }

// Notifies the observer
void InputObservable::notify(const SDL_Rect &rect) {
    _observer.update(rect);
}

// Polls the key input events
void InputObservable::pollEvents(SDL_Rect &rect) {
    SDL_Event event;

    if(SDL_PollEvent(&event)) {
        switch(event.type) {
            // On exit
            case SDL_QUIT:
                _closed = true; // sets _closed to true so that we exit the loop and exit the program
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        _closed = true;
                        break;
                    case SDLK_LEFT:
                        rect.x -= 10;
                        notify(rect);
                        break;
                    case SDLK_RIGHT:
                        rect.x += 10;
                        notify(rect);
                        break;
                    case SDLK_UP:
                        rect.y -= 10;
                        notify(rect);
                        break;
                    case SDLK_DOWN:
                        rect.y += 10;
                        notify(rect);
                        break;
                    default:
                        break;
                }
            default:
                break;
        }
    }
}