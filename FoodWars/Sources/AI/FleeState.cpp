#include <iostream>
#include "../../Headers/AI/FleeState.h"

FleeState::FleeState(EntityManager* entityManager, std::shared_ptr<AudioFacade> audioFacade, int entityId) : State(entityManager, std::move(audioFacade), entityId) {

}

void FleeState::enter() {
    std::cout << "Entering flee state" << std::endl;
}

void FleeState::execute(double dt) {
    std::cout << "Executing flee state" << std::endl;
}

void FleeState::exit() {

}