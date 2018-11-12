#include <utility>

#include <utility>
#include "../../Headers/StateMachine/ScreenStateManager.h"

ScreenStateManager::ScreenStateManager() : _currentState(nullptr) {

}

std::shared_ptr<IScreen> ScreenStateManager::getCurrentState() {
    return _currentState;
}

void ScreenStateManager::setWindowResolutionCalculator(std::shared_ptr<WindowResolutionCalculator> windowResCalc) {
    _windowResCalc = std::move(windowResCalc);
}