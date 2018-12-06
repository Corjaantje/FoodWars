#include <iostream>
#include "../../Headers/AI/AttackState.h"

void AttackState::enter() {
    std::cout << "Entering attack state" << std::endl;
}

void AttackState::execute(double dt) {
    std::cout << "Executing attack state" << std::endl;
}

void AttackState::exit() {

}