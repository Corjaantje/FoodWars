#include <utility>

//
// Created by Lucas on 11/10/2018.
//

#include "../../Headers/StateMachine/ScreenState.h"

ScreenState::ScreenState() : _currentState(nullptr) {

}

ScreenPtr* ScreenState::getCurrentState() {
    return &_currentState;
}

void ScreenState::setState(ScreenPtr screen) {
    this->_currentState = std::move(screen);
}

void ScreenState::setState(IScreen *screen) {
    this->_currentState = ScreenPtr{screen};
}

