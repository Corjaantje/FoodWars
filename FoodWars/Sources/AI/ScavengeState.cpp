#include <utility>
#include "../../Headers/AI/ScavengeState.h"
#include "../../Headers/GameECS/Systems/AISystem.h"
#include "../../Headers/AI/IdleState.h"
#include <iostream>

void ScavengeState::enter() {
    std::cout << "Entering scavenge state" << std::endl;
}

void ScavengeState::execute(double dt) {
    // if not my turn, switch to idle state
    // if my turn, calculate new state
    if(!_entityManager->getComponentFromEntity<TurnComponent>(_entityId)->isMyTurn())
    {
        // Idle state
        auto aiComponent = _entityManager->getComponentFromEntity<AIComponent>(_entityId);
        aiComponent->setCurrentState(std::make_unique<IdleState>(*_entityManager, _entityId, *_context));
    }
    // else
    std::cout << "Executing scavenge state" << std::endl;
    auto moveComponent = _entityManager->getComponentFromEntity<MoveComponent>(_entityId);
    auto turnComponent = _entityManager->getComponentFromEntity<TurnComponent>(_entityId);
    walkRight(*moveComponent, *turnComponent, dt);
}

void ScavengeState::exit() {

}

ScavengeState::ScavengeState(EntityManager &entityManager, int entityId, AISystem &context) : State(entityManager,
                                                                                            entityId,
                                                                                            context),
                                                                                      CollisionEventHandler(context.getCollisionEventObservable()) {

}

void ScavengeState::handleCollisionEvent(const CollisionEvent &collisionEvent) {
    // what to do now
    std::cout << "boop2";
    // Check if its the side of a block
}

bool ScavengeState::canHandle(const CollisionEvent &collisionEvent) {
    return collisionEvent.getEntity() == _entityId;
}