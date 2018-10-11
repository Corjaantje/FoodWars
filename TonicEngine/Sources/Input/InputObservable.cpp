//
// Created by svanr on 10/4/2018.
//

#include "../../Headers/Input/InputObservable.h"

InputObservable::InputObservable() {
    init();
}

InputObservable::~InputObservable() {
    delete _keyEvent;
}

void InputObservable::init() {
    _keyEvent = new KeyEvent();
    _observerMap = new std::map<IEvent, std::vector<IObserver>>();
}

// Registers the observer
void InputObservable::registerObserver(IObserver& iObserver) {
    _observerList.push_back(iObserver);
}

// Notifies all the observers
void InputObservable::notify(SDL_Event event) {
    if (!_observerList.empty()) {
        for (int i = 0; i < _observerList.size(); i++)
            _observerList[i].update(getEvent(event));
    }
}

// Returns the event from the dictionary by searching with our key
IEvent InputObservable::getEvent(SDL_Event eventName) {
    IEvent event = _eventMap->find(eventName)->second;
    return event;
}

// Polls the key input events
void InputObservable::pollEvents() {
    SDL_Event event;

    if(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_KEYDOWN: // When a key is pressed
                _keyEvent->setKey(event);
                _eventMap->insert(std::pair<SDL_Event, IEvent>(event, *_keyEvent));
                //_observerMap->insert(std::pair<IEvent, std::vector<IObserver*>>(*_keyEvent, _observerList));
                notify(event); // notifies the observers with our custom event
                break;
            default:
                break;
        }
    }
}

