#include "../../../Headers/GameECS/Systems/DamageableSystem.h"
#include "../../../Headers/GameECS/Components/DamagingComponent.h"
#include "../../../Headers/GameECS/Components/PlayerComponent.h"
#include "../../../Headers/GameECS/Components/TurnComponent.h"
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

    for (auto splashDamage = _splashDamages.begin(); splashDamage != _splashDamages.end();) {
        splashDamage->increaseTime(deltaTime);
        if (splashDamage->remove()) {
            splashDamage->hide();
            splashDamage = _splashDamages.erase(splashDamage);
            continue;
        }
        ++splashDamage;
    }
}

bool DamageableSystem::canHandle(const CollisionEvent &collisionEvent) {
    if(_entityManager->getComponentFromEntity<DamagingComponent>(collisionEvent.getEntity()) && _entityManager->getComponentFromEntity<DamageableComponent>(collisionEvent.getOtherEntity()))
        handleCollisionEvent(collisionEvent.getEntity(), collisionEvent.getOtherEntity());
    else if(_entityManager->getComponentFromEntity<DamagingComponent>(collisionEvent.getOtherEntity()) && _entityManager->getComponentFromEntity<DamageableComponent>(collisionEvent.getEntity()))
        handleCollisionEvent(collisionEvent.getOtherEntity(), collisionEvent.getEntity());
    return false;
}


void DamageableSystem::handleCollisionEvent(int projectileId, int targetId) {
    auto projectile = _entityManager->getComponentFromEntity<DamageableComponent>(projectileId);
    auto projectileDamage = _entityManager->getComponentFromEntity<DamagingComponent>(projectileId);
    projectile->destroy();
    auto target = _entityManager->getComponentFromEntity<DamageableComponent>(targetId);
    auto player = _entityManager->getComponentFromEntity<PlayerComponent>(targetId);

    int damage = 0;
    if (player == nullptr)damage = projectileDamage->getDamage() - target->getResistance();
    else damage = _damageCalculator.calculateDamage(*projectileDamage, *target, *player);
    if (damage > 0) target->lowerHealth(damage);

    if (player) {
        _splashDamages.emplace_back(*_entityManager, targetId);
        _audioFacade->playEffect("oof");
    } else {
        _audioFacade->playEffect("damage");
    }

    // Default point increase/decrease
    int iPoints = 10;
    std::map<int, PlayerComponent*> players = _entityManager->getAllEntitiesWithComponent<PlayerComponent>();
    for (auto const &player : players) {
        if (player.first == targetId) {
            player.second->addScore(-iPoints);
            iPoints = damage;
        }
    }
    for (auto const& turn : _entityManager->getAllEntitiesWithComponent<TurnComponent>()){
        if (turn.second->isMyTurn()) {
            players[turn.first]->addScore(iPoints);
        }
    }
    _entityManager->removeComponentFromEntity<DamagingComponent>(projectileId);
}