#include <utility>

#include <iostream>
#include "../../Headers/AI/IdleState.h"
#include "../../Headers/GameECS/Components/AIComponent.h"
#include "../../Headers/AI/ScavengeState.h"

void IdleState::enter() {
    std::cout << "Entering idle state" << std::endl;
}

void IdleState::execute(double dt) {
    std::cout << "Executing idle state" << std::endl;
    // if my turn, calculate new state
    if(_entityManager->getComponentFromEntity<TurnComponent>(_entityId)->isMyTurn())
    {
        // Scavenge state
        auto aiComponent = _entityManager->getComponentFromEntity<AIComponent>(_entityId);
        aiComponent->setCurrentState(std::make_unique<ScavengeState>(*_entityManager, _entityId, *_context));
    }
}

void IdleState::exit() {

}

IdleState::IdleState(EntityManager &entityManager, int entityId, AISystem &context) : State(entityManager,
                                                                                            entityId,
                                                                                            context) {

}
