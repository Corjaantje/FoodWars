//
// Created by svanr on 10/8/2018.
//

#ifndef PROJECT_SWA_KEYEVENT_H
#define PROJECT_SWA_KEYEVENT_H

#include <iostream>
#include <vector>
#include <SDL2/SDL_events.h>
#include "IEvent.h"
#include "../Input/IObserver.h"

enum class KEY {
    KEY_W,
    KEY_A,
    KEY_S,
    KEY_D,
    KEY_ESCAPE,
    KEY_PAGEUP,
    KEY_PAGEDOWN,
    KEY_HOME,
    KEY_OTHER
};

enum class KeyEventType {
    Down,
    Up
};

class KeyEvent: public IEvent {
private:
    KEY _pressedKey;
    KeyEventType _eventType;
public:
    KeyEvent(KEY pressedKey, KeyEventType eventType);
    KEY getKey() const;
    KeyEventType getKeyEventType();
};

#endif //PROJECT_SWA_KEYEVENT_H
