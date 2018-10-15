//
// Created by pietb on 11-Oct-18.
//

#include "../../../Headers/GameECS/Systems/TurnSystem.h"

TurnSystem::TurnSystem() {

}

TurnSystem::TurnSystem(int turnTime): _timePerTurn(turnTime) {
    //:_timePerTurn(turnTime*60)
}

TurnSystem::~TurnSystem() {

}

int TurnSystem::timePassed() {
    _timePerTurn--;
    return 0;
}

void TurnSystem::onUpdate(double deltaTime) {
    if (_startTime)
    {
        _remainingTime -= deltaTime;
//        _remainingTime = (_remainingTime > 0) ? _remainingTime - deltaTime : 30;
        if (_remainingTime <= 0)
        {
            _remainingTime = (float)_timePerTurn;
            // TODO
            // End turn of whomever's currently in charge
        }
    }
}

void TurnSystem::startTime() {
    _startTime = true;
    _remainingTime = (float)_timePerTurn;
}
