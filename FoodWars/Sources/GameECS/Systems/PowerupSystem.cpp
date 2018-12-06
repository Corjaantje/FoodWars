#include "../../../Headers/GameECS/Systems/PowerupSystem.h"

PowerupSystem::PowerupSystem(EntityManager &entityManager) : _entityManager(&entityManager) {

}

PowerupSystem::~PowerupSystem() = default;

void PowerupSystem::update(double dt) {
    if (rand() % 2 == 0) {

    } else {

    }
}
