//
// Created by svanr on 10/4/2018.
//

#ifndef PROJECT_SWA_IOBSERVABLE_H
#define PROJECT_SWA_IOBSERVABLE_H

#include <iostream>
#include <SDL2/SDL_events.h>
#include "../Events/IEvent.h"
#include "IObserver.h"

class IObservable {
public:
    IObservable() {

    }
    virtual void registerObserver(IObserver& iObserver) = 0;
    virtual void notify(SDL_Event event) = 0;
};

#endif //PROJECT_SWA_IOBSERVABLE_H
