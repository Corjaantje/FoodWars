#include "../../../Headers/GameECS/Systems/DamageableSystem.h"
#include "../../../Headers/GameECS/Components/DamagingComponent.h"

DamageableSystem::DamageableSystem(EntityManager &entityManager,
                                   IObservable<CollisionEvent>& collisionEventObservable) :
        _entityManager{&entityManager},
        CollisionEventHandler(collisionEventObservable) {
}

DamageableSystem::~DamageableSystem() = default;

void DamageableSystem::update(double deltaTime) {
    for (auto x : _entityManager->getAllEntitiesWithComponent<DamageableComponent>()) {
        if(!x.second->IsAlive())
        {
            _entityManager->removeEntity(x.first);
        }
    }
}

bool DamageableSystem::canHandle(const CollisionEvent &collisionEvent) {
    int target = collisionEvent.getEntity();
    int projectile = collisionEvent.getOtherEntity();
    return _entityManager->getComponentFromEntity<DamagingComponent>(target) &&
           _entityManager->getComponentFromEntity<DamageableComponent>(projectile);
}

void DamageableSystem::handleCollisionEvent(const CollisionEvent &collisionEvent)
{
    auto projectile = _entityManager->getComponentFromEntity<DamageableComponent>(collisionEvent.getEntity());
    projectile->Destroy();
    auto target = _entityManager->getComponentFromEntity<DamageableComponent>(collisionEvent.getOtherEntity());
    target->LowerHealth(
            _entityManager->getComponentFromEntity<DamagingComponent>(collisionEvent.getEntity())->getDamage());

    std::cout << "currentHP: " << target->GetHealth() << std::endl;
}
