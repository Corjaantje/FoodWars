#include "../../Headers/AI/ScavengeState.h"
#include <iostream>

ScavengeState::ScavengeState(MoveComponent* moveComponent, TurnComponent* turnComponent) : _moveComponent(moveComponent), _turnComponent(turnComponent) {

}

void ScavengeState::enter(){
    std::cout << "Entering scavenge state" << std::endl;
}

void ScavengeState::execute(double dt) {
    std::cout << "Executing scavenge state" << std::endl;
    walkRight(_moveComponent, _turnComponent, dt);
}

void ScavengeState::exit() {

}