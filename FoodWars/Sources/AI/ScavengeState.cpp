#include <utility>

#include "../../Headers/AI/ScavengeState.h"
#include <iostream>

ScavengeState::ScavengeState(EntityManager* entityManager, std::shared_ptr<AudioFacade> audioFacade, int entityId) : State(entityManager, std::move(audioFacade), entityId) {

}

void ScavengeState::enter(){
    std::cout << "Entering scavenge state" << std::endl;
}

void ScavengeState::execute(double dt) {
    std::cout << "Executing scavenge state" << std::endl;
    auto moveComponent = _entityManager->getComponentFromEntity<MoveComponent>(_entityId);
    auto turnComponent = _entityManager->getComponentFromEntity<TurnComponent>(_entityId);
    walkRight(*moveComponent, *turnComponent, dt);
}

void ScavengeState::exit() {

}