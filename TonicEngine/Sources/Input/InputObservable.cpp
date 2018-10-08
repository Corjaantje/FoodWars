//
// Created by svanr on 10/4/2018.
//

#include "../../Headers/Input/InputObservable.h"

InputObservable::InputObservable() {
    init();
    KeyEvent keyEvent;
    keyEvent.notify();
}

InputObservable::~InputObservable() {
    delete _keyEvent;
    delete _eventMap;
}

void InputObservable::init() {
    _keyEvent = new KeyEvent();
    _eventMap = new std::map<std::string, IEvent>();

    // Inserts the key in string format with a key event
    _eventMap->insert(std::pair<std::string,IEvent>("w", *_keyEvent));
    _eventMap->insert(std::pair<std::string,IEvent>("a", *_keyEvent));
    _eventMap->insert(std::pair<std::string,IEvent>("s", *_keyEvent));
    _eventMap->insert(std::pair<std::string,IEvent>("d", *_keyEvent));
}

// Registers the observer
void InputObservable::registerObserver(IObserver& iObserver) {
    _observerList.push_back(&iObserver);
}

// Notifies all the observers
void InputObservable::notify(IEvent keyEvent) {
    if (!_observerList.empty()) {
        for (int i = 0; i < _observerList.size(); i++)
            _observerList[i]->update(keyEvent);
    }
}

// Returns the event from the dictionary by searching with our key
IEvent InputObservable::getEvent(std::string eventName) {
    IEvent event = _eventMap->find(eventName)->second;
    return event;
}

// Polls the key input events
void InputObservable::pollEvents() {
    SDL_Event event;

    if(SDL_PollEvent(&event)) {
        IEvent customEvent;

        switch(event.type) {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {  // When a key is pressed
                    case SDLK_w:
                        customEvent = getEvent("w");
                        break;
                    case SDLK_a:
                        customEvent = getEvent("a");
                        break;
                    case SDLK_s:
                        customEvent = getEvent("s");
                        break;
                    case SDLK_d:
                        customEvent = getEvent("d");
                        break;
                    default:
                        break;
                }
                notify(customEvent); // notifies the observers with our custom event
                break;
            default:
                break;
        }
    }
}

