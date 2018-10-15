//
// Created by svanr on 10/8/2018.
//

#include "../../Headers/Events/KeyEvent.h"

void KeyEvent::setKey(SDL_Event event) {
    if (event.key.keysym.sym == SDLK_w)
        _pressedKey = KEY_W;
    else if (event.key.keysym.sym == SDLK_a)
        _pressedKey = KEY_A;
    else if (event.key.keysym.sym == SDLK_s)
        _pressedKey = KEY_S;
    else if (event.key.keysym.sym == SDLK_d)
        _pressedKey = KEY_D;
}

KeyEvent::KEYS KeyEvent::getKey() const {
    return _pressedKey;
}

/*void KeyEvent::registerObserver(IObserver& iObserver) {
    _observerList.push_back(&iObserver);
}*/

void KeyEvent::notify() {
    if (!_observerList.empty()) {
        for (int i = 0; i < _observerList.size(); i++)
            _observerList[i]->update();
    }
}
