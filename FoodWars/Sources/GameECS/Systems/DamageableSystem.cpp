#include "../../../Headers/GameECS/Systems/DamageableSystem.h"
#include "../../../Headers/GameECS/Components/DamagingComponent.h"
#include "../../../Headers/GameECS/Components/PlayerComponent.h"
#include <cmath>

DamageableSystem::DamageableSystem(EntityManager &entityManager, AudioFacade& audioFacade,
                                   IObservable<CollisionEvent>& collisionEventObservable) :
        _entityManager{&entityManager},
        _audioFacade{&audioFacade},
        CollisionEventHandler(collisionEventObservable),
        _damageCalculator{DamageCalculator{}}{
}

DamageableSystem::~DamageableSystem() = default;

void DamageableSystem::update(double deltaTime) {
    for (auto x : _entityManager->getAllEntitiesWithComponent<DamageableComponent>()) {
        if(!x.second->isAlive())
        {
            auto* playerComp = _entityManager->getComponentFromEntity<PlayerComponent>(x.first);
            if(playerComp == nullptr) {
                _entityManager->removeEntity(x.first);
            }
            //We've killed a player!
            else{
                playerComp->setIsAlive(false);
            }
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
    auto projectileDamage = _entityManager->getComponentFromEntity<DamagingComponent>(collisionEvent.getEntity());
    projectile->destroy();
    auto target = _entityManager->getComponentFromEntity<DamageableComponent>(collisionEvent.getOtherEntity());
    auto player = _entityManager->getComponentFromEntity<PlayerComponent>(collisionEvent.getOtherEntity());

    int damage = 0;
    if (player == nullptr) {
        damage = projectileDamage->getDamage() - target->getResistance();
    } else {
        damage = _damageCalculator.calculateDamage(*projectileDamage, *target, *player);
    }
    if (damage > 0) target->lowerHealth(damage);

    _audioFacade->playEffect("damage");
}
