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
#include "../Events/WindowEvent.h"
#include "KeyEventObservable.h"
#include "MouseEventObservable.h"
#include "../../Facades/IFacade.h"
#include "WindowEventObservable.h"
#include "../General/WindowResolutionCalculator.h"

#ifndef PROJECT_SWA_INPUTOBSERVABLE_H
#define PROJECT_SWA_INPUTOBSERVABLE_H

class InputFacade : public IFacade {
private:
    KeyEventObservable _keyEventObservable;
    MouseEventObservable _mouseEventObservable;
    WindowEventObservable _windowEventObservable;
    int eventFilter(const SDL_Event* event);
    std::map<SDL_Keycode, KEY> _keycodeMap;
    const WindowResolutionCalculator* _windowResCalc;
    void init();
public:
    InputFacade();
    ~InputFacade();

    const KeyEventObservable& getKeyEventObservable() const;
    const MouseEventObservable& getMouseEventObservable() const;
    const WindowEventObservable& getWindowEventObservable() const;
    KeyEventObservable& getKeyEventObservable();
    MouseEventObservable& getMouseEventObservable();
    WindowEventObservable& getWindowEventObservable();
    void setWindowResolutionCalculator(const WindowResolutionCalculator& windowResCalc);
    void pollEvents();
};

#endif //PROJECT_SWA_INPUTOBSERVABLE_H