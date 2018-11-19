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
            std::cout <<"HELEMAAL KAPOT" << std::endl;
            _entityManager->removeEntity(x.first);
        }
    }
}

bool DamageableSystem::canHandle(const CollisionEvent &collisionEvent) {
    int target = collisionEvent.getEntity();
    int projectile = collisionEvent.getOtherEntity();
    if (_entityManager->getComponentFromEntity<DamagingComponent>(projectile) &&
            _entityManager->getComponentFromEntity<DamageableComponent>(target)) {
        return true;
    }
    return _entityManager->getComponentFromEntity<DamagingComponent>(target) &&
           _entityManager->getComponentFromEntity<DamageableComponent>(projectile);
}

void DamageableSystem::handleCollisionEvent(const CollisionEvent &collisionEvent)
{
    //remove projectile
    if (_entityManager->getComponentFromEntity<DamagingComponent>(collisionEvent.getEntity()))
    {
        _entityManager->removeEntity(collisionEvent.getEntity());
    }
    //lower target health
    else if (_entityManager->getComponentFromEntity<DamageableComponent>(collisionEvent.getEntity())) {
        _entityManager->getComponentFromEntity<DamageableComponent>(collisionEvent.getEntity())->LowerHealth(20);
    }
    //remove projectile
    if (_entityManager->getComponentFromEntity<DamagingComponent>(collisionEvent.getOtherEntity()))
    {
        _entityManager->removeEntity(collisionEvent.getOtherEntity());
    }
    //lower target health
    else {
        _entityManager->getComponentFromEntity<DamageableComponent>(collisionEvent.getOtherEntity())->LowerHealth(20);
    }
}
