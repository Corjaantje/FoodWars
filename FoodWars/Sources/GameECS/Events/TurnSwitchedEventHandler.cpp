//
// Created by bryanvanlierop on 12/13/2018.
//

#include "../../../Headers/GameECS/Events/TurnSwitchedEventHandler.h"
void TurnSwitchedEventHandler::update(const TurnSwitchedEvent& turnSwitchedEvent) {
    handleTurnSwitchedEvent(turnSwitchedEvent);
}

TurnSwitchedEventHandler::TurnSwitchedEventHandler(IObservable<TurnSwitchedEvent> &turnSwitchedEventObservable) {
    turnSwitchedEventObservable.registerObserver(this);
}
