#include <utility>
#include "../../Headers/StateMachine/ScreenStateManager.h"

ScreenStateManager::ScreenStateManager() : _currentState(nullptr) {

}

std::shared_ptr<IScreen> ScreenStateManager::getCurrentState() {
    return _currentState;
}

void ScreenStateManager::setActiveScreen(const std::string &screenName) {
    if(_screenStates.count(screenName) > 0){
        _currentState = _screenStates[screenName];
    }
}
