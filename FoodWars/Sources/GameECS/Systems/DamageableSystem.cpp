#include "../../../Headers/GameECS/Systems/DamageableSystem.h"
#include "../../../Headers/GameECS/Components/TurnComponent.h"
#include "../../../Headers/GameECS/Components/DamagingComponent.h"

DamageableSystem::DamageableSystem(std::shared_ptr<EntityManager> entityManager,
        IObservable<CollisionEvent>& collisionEventObservable) :
                                                _entityManager{std::move(entityManager)},
                                                CollisionEventHandler(collisionEventObservable) {}

DamageableSystem::~DamageableSystem() = default;

void DamageableSystem::update(double deltaTime) {
    _damageableComponents = _entityManager->getAllEntitiesWithComponent<DamageableComponent>();
    for(auto x : _damageableComponents)
    {
        if (x.second == nullptr)
        {
            break;
        }
        if(!x.second->IsAlive())
        {
            _entityManager->removeEntity(x.first);
        }
    }
}

bool DamageableSystem::canHandle(const CollisionEvent &collisionEvent) {
    int target = collisionEvent.getEntity();
    int projectile = collisionEvent.getOtherEntity();
    /*if (_entityManager->getComponentFromEntity<DamagingComponent>(projectile) &&
            _entityManager->getComponentFromEntity<DamageableComponent>(target)) {
        return true;
    }*/
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
