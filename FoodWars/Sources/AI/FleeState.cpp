#include <iostream>
#include "../../Headers/AI/FleeState.h"

void FleeState::enter() {
    std::cout << "Entering flee state" << std::endl;
}

void FleeState::execute(double dt) {
    std::cout << "Executing flee state" << std::endl;
}

void FleeState::exit() {

}