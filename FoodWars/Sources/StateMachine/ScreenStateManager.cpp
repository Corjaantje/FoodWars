#include <utility>

//
// Created by Lucas on 11/10/2018.
//

#include "../../Headers/StateMachine/ScreenStateManager.h"

ScreenStateManager::ScreenStateManager() : _currentState(nullptr) {

}

std::shared_ptr<IScreen> ScreenStateManager::getCurrentState() {
    return _currentState;
}