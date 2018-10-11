//
// Created by svanr on 10/8/2018.
//

#ifndef PROJECT_SWA_IEVENT_H
#define PROJECT_SWA_IEVENT_H

#include "../Input/IObserver.h"

class IEvent {
public:
    IEvent() {

    }
    virtual void registerObserver(IObserver& iObserver);
    virtual void notify();
};

#endif //PROJECT_SWA_IEVENT_H


