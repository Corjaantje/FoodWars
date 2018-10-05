//
// Created by svanr on 10/4/2018.
//

#include "../../Headers/Input/InputObservable.h"

InputObservable::InputObservable() {
}

InputObservable::~InputObservable() {
}

// Registers the observer
void InputObservable::registerObserver(IObserver& iObserver) {
    _observerList.push_back(&iObserver);
}

// Notifies all the observers
void InputObservable::notify(std::string key) {
    if (!_observerList.empty()) {
        for (int i = 0; i < _observerList.size(); i++)
            _observerList[i]->update(key);
    }
}

// Polls the key input events
void InputObservable::pollEvents() {
    SDL_Event event;
    if(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_LEFT:
                        notify("left");
                        break;
                    case SDLK_RIGHT:
                        notify("right");
                        break;
                    case SDLK_UP:
                        notify("up");
                        break;
                    case SDLK_DOWN:
                        notify("down");
                        break;
                    default:
                        break;
                }
            default:
                break;
        }
    }
}

