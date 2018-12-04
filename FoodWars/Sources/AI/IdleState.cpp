#include <iostream>
#include "../../Headers/AI/IdleState.h"

void IdleState::enter() {
    std::cout << "Entering idle state" << std::endl;
}

void IdleState::execute(double dt) {
    std::cout << "Executing idle state" << std::endl;
}

void IdleState::exit() {

}
