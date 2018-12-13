//
// Created by bryanvanlierop on 12/13/2018.
//

#ifndef PROJECT_SWA_TURNSWITCHEDEVENTHANDLER_H
#define PROJECT_SWA_TURNSWITCHEDEVENTHANDLER_H

#include "TurnSwitchedEvent.h"
#include "../../../../TonicEngine/Headers/Input/IObservable.h"

class TurnSwitchedEventHandler : IObserver<TurnSwitchedEvent> {
public:
    TurnSwitchedEventHandler(IObservable<TurnSwitchedEvent>& turnSwitchedEventObservable);
    virtual void handleTurnSwitchedEvent(const TurnSwitchedEvent& turnSwitchedEvent) = 0;
    void update(const TurnSwitchedEvent& turnSwitchedEvent) final;
};
#endif //PROJECT_SWA_TURNSWITCHEDEVENTHANDLER_H
