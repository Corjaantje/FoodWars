#include "../../Headers/AI/ScavengeState.h"
#include <iostream>

void ScavengeState::enter(){
    std::cout << "Entering scavenge state" << std::endl;
}

void ScavengeState::execute(double dt) {
    std::cout << "Executing scavenge state" << std::endl;
    walkRight(*moveComponent, *turnComponent, dt);
}

void ScavengeState::exit() {

}