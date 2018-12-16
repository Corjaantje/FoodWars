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
    if (modifiedTime >= 0 && modifiedTime <= 2.40)
        timeModifier = modifiedTime;
}

double ScreenStateManager::getTimeModifier() const {
    return timeModifier;
}

LevelLoader& ScreenStateManager::getLevelManager() const {
    return *_levelManager;
}

void ScreenStateManager::setLevelManager(LevelLoader &levelManager) {
    _levelManager = &levelManager;
}
