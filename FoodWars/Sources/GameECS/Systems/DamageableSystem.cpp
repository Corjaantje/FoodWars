#include "../../../Headers/GameECS/Systems/DamageableSystem.h"
#include "../../../Headers/GameECS/Components/DamagingComponent.h"
#include "../../../Headers/GameECS/Events/CollisionEventHandlerLamda.h"

DamageableSystem::DamageableSystem(std::shared_ptr<EntityManager> entityManager,
        IObservable<CollisionEvent>& collisionEventObservable) :
                                                _entityManager{std::move(entityManager)},
                                                CollisionEventHandler(collisionEventObservable) {
}

DamageableSystem::~DamageableSystem() = default;

void DamageableSystem::update(double deltaTime) {
    _damageableComponents = _entityManager->getAllEntitiesWithComponent<DamageableComponent>();
    for(auto x : _damageableComponents)
    {
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
    target->LowerHealth(_entityManager->getComponentFromEntity<DamagingComponent>(collisionEvent.getEntity())->GetDamage());

    std::cout << "currentHP: " << target->GetHealth() << std::endl;
}
