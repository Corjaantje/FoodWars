#include <memory>

#include "../../Headers/Input/InputFacade.h"

InputFacade::InputFacade() {
    init();
}

InputFacade::~InputFacade() {

}

void InputFacade::init() {
    _keyEventObservable = std::make_shared<KeyEventObservable>();
    _mouseEventObservable = std::make_shared<MouseEventObservable>();
    _windowEventObservable = std::make_shared<WindowEventObservable>();
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
                std::shared_ptr<KeyEvent> keyEvent = std::make_shared<KeyEvent>(_keycodeMap[event.key.keysym.sym], KeyEventType::Down);
                _keyEventObservable.get()->notify(keyEvent);
                break;
            }
            case SDL_MOUSEBUTTONDOWN: { // When a click is registered
                std::shared_ptr<MouseEvent> mouseEvent = std::make_shared<MouseEvent>(event.motion.x, event.motion.y);
                _mouseEventObservable.get()->notify(mouseEvent);
                break;
            }
            case SDL_QUIT: { // When the window is closed
                std::shared_ptr<WindowEvent> windowEvent = std::make_shared<WindowEvent>();
                _windowEventObservable.get()->closeWindow();
                break;
            }
            case SDL_WINDOWEVENT_RESIZED:
                break;
            case SDL_WINDOW_MAXIMIZED:
                break;
            case SDL_WINDOW_MINIMIZED:
                break;_
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

bool InputFacade::isWindowClosed() {
    return _windowEventObservable->isClosed();
}

