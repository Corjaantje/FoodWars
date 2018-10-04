//
// Created by svanr on 10/1/2018.
//

#include "InputSystem.h"

#ifndef PROJECT_SWA_INPUTOBSERVABLE_H
#define PROJECT_SWA_INPUTOBSERVABLE_H

#endif //PROJECT_SWA_INPUTOBSERVABLE_H

class InputObservable {
public:
    InputObservable(InputSystem observer);
    void notify(const SDL_Rect &rect);
    void pollEvents(SDL_Rect &rect);

    inline bool isClosed() const { return _closed; }
private:
    InputSystem _observer;
    bool _closed = false;
};