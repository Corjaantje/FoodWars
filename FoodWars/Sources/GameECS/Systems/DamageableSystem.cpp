#include "../../../Headers/GameECS/Systems/DamageableSystem.h"
#include "../../../Headers/GameECS/Components/DamagingComponent.h"
#include "../../../Headers/GameECS/Components/PlayerComponent.h"
#include <cmath>

DamageableSystem::DamageableSystem(EntityManager &entityManager, AudioFacade& audioFacade,
                                   IObservable<CollisionEvent>& collisionEventObservable) :
        _entityManager{&entityManager},
        _audioFacade{&audioFacade},
        CollisionEventHandler(collisionEventObservable) {
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
    if(_entityManager->getComponentFromEntity<DamagingComponent>(projectile) && _entityManager->getComponentFromEntity<DamageableComponent>(target)){
        handleInvertedCollisionEvent(collisionEvent);
        return false;
    }
    return _entityManager->getComponentFromEntity<DamagingComponent>(target) && _entityManager->getComponentFromEntity<DamageableComponent>(projectile);
}

void DamageableSystem::handleCollisionEvent(const CollisionEvent &collisionEvent)
{
    auto projectile = _entityManager->getComponentFromEntity<DamageableComponent>(collisionEvent.getEntity());
    projectile->destroy();
    auto target = _entityManager->getComponentFromEntity<DamageableComponent>(collisionEvent.getOtherEntity());
    auto damage = _entityManager->getComponentFromEntity<DamagingComponent>(collisionEvent.getEntity())->getDamage();
    double damageTaken =  damage - (damage * (target->getResistance()/100.0));
    if (damageTaken > 0) target->lowerHealth((int) std::round(damageTaken));
    _audioFacade->playEffect("damage");

    std::cout << "currentHP: " << target->getHealth() << std::endl;
}

void DamageableSystem::handleInvertedCollisionEvent(const CollisionEvent &collisionEvent)
{
    auto projectile = _entityManager->getComponentFromEntity<DamageableComponent>(collisionEvent.getOtherEntity());
    projectile->Destroy();
    auto target = _entityManager->getComponentFromEntity<DamageableComponent>(collisionEvent.getEntity());
    target->LowerHealth(_entityManager->getComponentFromEntity<DamagingComponent>(collisionEvent.getOtherEntity())->getDamage());

    std::cout << "Inverted handle, currentHP: " << target->GetHealth() << std::endl;
}
