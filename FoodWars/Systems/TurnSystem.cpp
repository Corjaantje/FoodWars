//
// Created by pietb on 11-Oct-18.
//

#include "TurnSystem.h"

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
    }
}

void TurnSystem::startTime() {
    _startTime = true;
    _remainingTime = (float)_timePerTurn;
}
