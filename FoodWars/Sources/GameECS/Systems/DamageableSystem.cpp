#include "../../../Headers/GameECS/Systems/DamageableSystem.h"

DamageableSystem::DamageableSystem(std::shared_ptr<EntityManager> entityManager) {
    _entityManager = entityManager;
    _damageableComponents = _entityManager->getAllEntitiesWithComponent<DamageableComponent>();
}

DamageableSystem::~DamageableSystem() = default;

void DamageableSystem::update(double deltaTime) {

}