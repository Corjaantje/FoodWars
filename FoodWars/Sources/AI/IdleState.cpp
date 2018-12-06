#include <iostream>
#include "../../Headers/AI/IdleState.h"

IdleState::IdleState(EntityManager* entityManager, std::shared_ptr<AudioFacade> audioFacade, int entityId) : State(entityManager, std::move(audioFacade), entityId) {

}

void IdleState::enter() {
    std::cout << "Entering idle state" << std::endl;
}

void IdleState::execute(double dt) {
    std::cout << "Executing idle state" << std::endl;
}

void IdleState::exit() {

}