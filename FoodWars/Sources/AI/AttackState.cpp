#include <utility>
#include <iostream>
#include "../../Headers/AI/AttackState.h"
#include "../../Headers/GameECS/Systems/AISystem.h"

void AttackState::enter() {
    std::cout << "Entering attack state" << std::endl;
}

void AttackState::execute(double dt) {
    std::cout << "Executing attack state" << std::endl;
}

void AttackState::exit() {

}

AttackState::AttackState(EntityManager &entityManager, int entityId, AISystem &context,
                         IObservable<CollisionEvent> &collisionEventObservable) : State(entityManager,
                                                                                        entityId,
                                                                                        context),
                                                                                  CollisionEventHandler(context.getCollisionEventObservable()) {

}
