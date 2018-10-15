//
// Created by svanr on 10/1/2018.
//

#include <vector>
#include <SDL2/SDL_events.h>
#include "IObservable.h"
#include <memory>
#include <map>
#include "../Events/KeyEvent.h"
#include "../Events/MouseEvent.h"
#include "KeyEventObservable.h"
#include "MouseEventObservable.h"

#ifndef PROJECT_SWA_INPUTOBSERVABLE_H
#define PROJECT_SWA_INPUTOBSERVABLE_H

class InputFacade {
private:
    std::shared_ptr<KeyEventObservable> _keyEventObservable;
    std::shared_ptr<MouseEventObservable> _mouseEventObservable;
    std::map<SDL_Keycode, KEY> _keycodeMap;
    void init();
public:
    InputFacade();
    ~InputFacade();

    std::shared_ptr<KeyEventObservable> getKeyEventObservable();
    std::shared_ptr<MouseEventObservable> getMouseEventObservable();
    void pollEvents();
};

#endif //PROJECT_SWA_INPUTOBSERVABLE_H