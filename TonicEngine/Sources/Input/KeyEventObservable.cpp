#include "../../Headers/Input/KeyEventObservable.h"

KeyEventObservable::KeyEventObservable() {
    _keycodeMap[SDL_SCANCODE_W] = KEY::KEY_W;
    _keycodeMap[SDL_SCANCODE_A] = KEY::KEY_A;
    _keycodeMap[SDL_SCANCODE_S] = KEY::KEY_S;
    _keycodeMap[SDL_SCANCODE_D] = KEY::KEY_D;
    _keycodeMap[SDL_SCANCODE_F] = KEY::KEY_F;
    _keycodeMap[SDL_SCANCODE_G] = KEY::KEY_G;
    _keycodeMap[SDL_SCANCODE_ESCAPE] = KEY::KEY_ESCAPE;
    _keycodeMap[SDL_SCANCODE_PAGEUP] = KEY::KEY_PAGEUP;
    _keycodeMap[SDL_SCANCODE_PAGEDOWN] = KEY::KEY_PAGEDOWN;
    _keycodeMap[SDL_SCANCODE_HOME] = KEY::KEY_HOME;
    _keycodeMap[SDL_SCANCODE_SPACE] = KEY::KEY_SPACEBAR;
    for (auto const &iterator: _keycodeMap) {
        _pressedKeys[iterator.second] = false;
    }
}

KeyEventObservable::~KeyEventObservable() {
}

void KeyEventObservable::update() {
    const Uint8 *keyBoardState = SDL_GetKeyboardState(nullptr);
    bool pressedKeysChanged = false;
    for(auto const &iterator: _keycodeMap) {
        if(keyBoardState[iterator.first]) { // key is pressed
            if(!_pressedKeys.at(iterator.second)) { // key is not pressed
                IObservable<KeyEvent>::notify(std::make_shared<KeyEvent>(iterator.second, KeyEventType::Down));
                _pressedKeys[iterator.second] = true;
                pressedKeysChanged = true;
            }

        } else { // key is not pressed
            if(_pressedKeys.at(iterator.second)) {
                IObservable<KeyEvent>::notify(std::make_shared<KeyEvent>(iterator.second, KeyEventType::Up));
                _pressedKeys[iterator.second] = false;
                pressedKeysChanged = true;
            }
        }
    }
    if(pressedKeysChanged)
        IObservable<std::map<KEY, bool>>::notify(std::make_shared<std::map<KEY, bool>>(_pressedKeys));
}

void KeyEventObservable::registerKeyEventObserver(IObserver<KeyEvent> *observer) {
    IObservable<KeyEvent>::registerObserver(observer);
}

void KeyEventObservable::registerKeyPressedMapObserver(IObserver<std::map<KEY, bool>> *observer) {
    IObservable<std::map<KEY, bool>>::registerObserver(observer);
}