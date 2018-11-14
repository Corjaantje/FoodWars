#include <utility>

#include <utility>
#include "../../Headers/StateMachine/ScreenStateManager.h"

ScreenStateManager::ScreenStateManager() : _currentState(nullptr) {

}

std::shared_ptr<IScreen> ScreenStateManager::getCurrentState() const {
    return _currentState;
}

void ScreenStateManager::setWindowResolutionCalculator(std::shared_ptr<WindowResolutionCalculator> windowResCalc) {
    _windowResCalc = std::move(windowResCalc);
}

void ScreenStateManager::setTimeModifier(double modifiedTime) {
    if (modifiedTime == 1)
        timeModifier = modifiedTime;
    else {
        double newTime = timeModifier * modifiedTime;

        if (newTime >= 0.40 && newTime <= 2.50)
            timeModifier = newTime;
    }
}

double ScreenStateManager::getTimeModifier() const {
    return timeModifier;
}