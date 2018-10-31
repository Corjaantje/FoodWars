#include "../../Headers/Input/KeyEventObservable.h"

KeyEventObservable::KeyEventObservable() {
    _keycodeMap[SDLK_w] = KEY::KEY_W;
    _keycodeMap[SDLK_a] = KEY::KEY_A;
    _keycodeMap[SDLK_s] = KEY::KEY_S;
    _keycodeMap[SDLK_d] = KEY::KEY_D;
    _keycodeMap[SDLK_ESCAPE] = KEY::KEY_ESCAPE;
    for (auto const &iterator: _keycodeMap) {
        _pressedKeys[iterator.second] = false;
    }
}

KeyEventObservable::~KeyEventObservable() {
}

void KeyEventObservable::update() const {
    const Uint8 *keyBoardState = SDL_GetKeyboardState(nullptr);

    for(auto const &iterator: _keycodeMap) {
       /* keyBoardState[iterator.first]
        _pressedKeys[iterator.first]*/
    }
}
