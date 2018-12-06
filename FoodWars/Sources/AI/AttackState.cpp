#include <iostream>
#include "../../Headers/AI/AttackState.h"

AttackState::AttackState(EntityManager* entityManager, std::shared_ptr<AudioFacade> audioFacade, int entityId) : State(entityManager, std::move(audioFacade), entityId) {

}

void AttackState::enter() {
    std::cout << "Entering attack state" << std::endl;
}

void AttackState::execute(double dt) {
    std::cout << "Executing attack state" << std::endl;
}

void AttackState::exit() {

}