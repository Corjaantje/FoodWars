#include <utility>
#include "../../Headers/StateMachine/ScreenStateManager.h"
#include "../../Headers/StateMachine/IScreen.h"

ScreenStateManager::ScreenStateManager() = default;
ScreenStateManager::~ScreenStateManager() = default;

IScreen& ScreenStateManager::getCurrentState() const {
    return *_currentState;
}

const WindowResolutionCalculator& ScreenStateManager::getWindowResolutionCalculator() const {
    return *_windowResCalc;
}

void ScreenStateManager::setWindowResolutionCalculator(const WindowResolutionCalculator& windowResCalc) {
    _windowResCalc = &windowResCalc;
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

LevelManager& ScreenStateManager::getLevelManager() const {
    return *_levelManager;
}

void ScreenStateManager::setLevelManager(LevelManager &levelManager) {
    _levelManager = &levelManager;
}
