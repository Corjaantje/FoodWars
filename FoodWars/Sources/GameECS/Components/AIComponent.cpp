#include "../../../Headers/GameECS/Components/AIComponent.h"

AIComponent::AIComponent(int id, int difficulty) : PlayerComponent(id), _difficulty(difficulty) {

}

int AIComponent::getDifficulty() const {
    return _difficulty;
}

void AIComponent::setCurrentState(std::unique_ptr<State> state) {
    if(_currentState) _currentState->exit();

        state->enter();
        _currentState = std::move(state);

}

void AIComponent::update(double dt) {
    if (_currentState) _currentState->execute(dt);
}