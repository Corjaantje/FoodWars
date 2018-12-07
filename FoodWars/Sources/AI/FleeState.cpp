#include <utility>
#include <iostream>
#include "../../Headers/AI/FleeState.h"
#include "../../Headers/GameECS/Systems/AISystem.h"

void FleeState::enter() {
    std::cout << "Entering flee state" << std::endl;
}

void FleeState::execute(double dt) {
    std::cout << "Executing flee state" << std::endl;
}

void FleeState::exit() {

}

FleeState::FleeState(EntityManager &entityManager, int entityId, AISystem &context,
                     IObservable<CollisionEvent> &collisionEventObservable) : State(entityManager,
                                                                                    entityId,
                                                                                    context),
                                                                              CollisionEventHandler(context.getCollisionEventObservable()) {

}
