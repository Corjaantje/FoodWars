#include "../../../Headers/GameECS/Components/AIComponent.h"

AIComponent::AIComponent(Difficulty difficulty) : _difficulty(difficulty), _currentState(nullptr) {

}

int AIComponent::getDifficulty() const {
    return _difficulty;
}

void AIComponent::setCurrentState(std::unique_ptr<State> state) {
    if(_currentState) _currentState->exit();
    state->enter();
    _currentState = std::move(state);
}

State* AIComponent::getCurrentState() const{
    return _currentState.get();
}

void AIComponent::update(double dt) {
    if (_currentState) _currentState->execute(dt);
}
