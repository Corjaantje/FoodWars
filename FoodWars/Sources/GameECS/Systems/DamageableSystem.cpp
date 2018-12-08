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
    if(_entityManager->getComponentFromEntity<DamagingComponent>(projectile) && _entityManager->getComponentFromEntity<DamageableComponent>(target)){
        handleInvertedCollisionEvent(collisionEvent);
        return false;
    }
    return _entityManager->getComponentFromEntity<DamagingComponent>(target) && _entityManager->getComponentFromEntity<DamageableComponent>(projectile);
}

void DamageableSystem::handleCollisionEvent(const CollisionEvent &collisionEvent)
{
    auto projectile = _entityManager->getComponentFromEntity<DamageableComponent>(collisionEvent.getEntity());
    projectile->Destroy();
    auto target = _entityManager->getComponentFromEntity<DamageableComponent>(collisionEvent.getOtherEntity());
    target->LowerHealth(_entityManager->getComponentFromEntity<DamagingComponent>(collisionEvent.getEntity())->getDamage());

    std::cout << "currentHP: " << target->GetHealth() << std::endl;
}

void DamageableSystem::handleInvertedCollisionEvent(const CollisionEvent &collisionEvent)
{
    auto projectile = _entityManager->getComponentFromEntity<DamageableComponent>(collisionEvent.getOtherEntity());
    projectile->Destroy();
    auto target = _entityManager->getComponentFromEntity<DamageableComponent>(collisionEvent.getEntity());
    target->LowerHealth(_entityManager->getComponentFromEntity<DamagingComponent>(collisionEvent.getOtherEntity())->getDamage());

    std::cout << "Inverted handle, currentHP: " << target->GetHealth() << std::endl;
}
