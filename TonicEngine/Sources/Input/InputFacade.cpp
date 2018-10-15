#include <memory>

#include "../../Headers/Input/InputFacade.h"

InputFacade::InputFacade() {
    init();
}

InputFacade::~InputFacade() {

}

void InputFacade::init() {
    _keyEventObservable = std::shared_ptr<KeyEventObservable>(new KeyEventObservable);
    _mouseEventObservable = std::shared_ptr<MouseEventObservable>(new MouseEventObservable);
    _keycodeMap[SDLK_w] = KEY::KEY_W;
    _keycodeMap[SDLK_a] = KEY::KEY_A;
    _keycodeMap[SDLK_s] = KEY::KEY_S;
    _keycodeMap[SDLK_d] = KEY::KEY_D;
}

// Polls the key input events
void InputFacade::pollEvents() {
    SDL_Event event;

    if(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_KEYDOWN: { // When a key is pressed
                std::shared_ptr<KeyEvent> keyEvent = std::shared_ptr<KeyEvent>(new KeyEvent(_keycodeMap[event.key.keysym.sym], KeyEventType::Down));
                _keyEventObservable.get()->notify(keyEvent);
                break;
            }
            case SDL_MOUSEBUTTONDOWN: { // When a click is registered
                int x, y;
                SDL_GetMouseState(&x, &y);
                std::shared_ptr<MouseEvent> mouseEvent = std::shared_ptr<MouseEvent>(new MouseEvent(x, y));
                _mouseEventObservable.get()->notify(mouseEvent);
                break;
            }
            default:
                break;
        }
    }
}

std::shared_ptr<KeyEventObservable> InputFacade::getKeyEventObservable() {
    return _keyEventObservable;
}

std::shared_ptr<MouseEventObservable> InputFacade::getMouseEventObservable() {
    return _mouseEventObservable;
}

