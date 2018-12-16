#include <utility>

#include <iostream>
#include "../../Headers/AI/IdleState.h"
#include "../../Headers/AI/WanderState.h"
#include "../../Headers/AI/AttackState.h"
#include "../../Headers/GameECS/Components/ItemComponent.h"
#include <math.h>

IdleState::IdleState(EntityManager &entityManager, int entityId, std::string previousState, AISystem &context) : State(entityManager, entityId, context),
                                                                                            _previousState(previousState) {

}

void IdleState::enter() {
    std::cout << "Entering idle state" << std::endl;
}

void IdleState::execute(double dt) {
    // Stop walking
    _moveComponent->xVelocity = 0;

    // if my turn, calculate new state
    if(_turnComponent->isMyTurn() && _turnComponent->getRemainingTime() > 0 && _turnComponent->getEnergy() > 0.0) {
        chooseState();
    }
}

void IdleState::exit() {

}


void IdleState::chooseState(){
    // Get closest powerup
    int closestItem = getClosestItem();
    // Get distance to enemy
    double distanceToEnemy = getDistanceToEnemy();
    // Get the amount of ammo
    int amountOfAmmo = getAmountOfAmmo();
    // Get energy
    double energy = _entityManager->getComponentFromEntity<TurnComponent>(_entityId)->getEnergy();
    // Check on own hp
    int myHealth = _entityManager->getComponentFromEntity<DamageableComponent>(_entityId)->getHealth();
    // Check on enemy hp
    int enemyHealth = getEnemyHealth();


    std::cout << "closestItem: " << closestItem << std::endl;
    std::cout << "distanceToEnemy: " << distanceToEnemy << std::endl;
    std::cout << "amountOfAmmo: " << amountOfAmmo << std::endl;
    std::cout << "energy: " << energy << std::endl;
    std::cout << "myHealth: " << myHealth << std::endl;
    std::cout << "enemyHealth: " << enemyHealth << std::endl;

    /*// any item drops?
    for(const auto& iterator: _entityManager->getAllEntitiesWithComponent<ItemComponent>()){
        auto itemPosition = _entityManager->getComponentFromEntity<PositionComponent>(iterator.first);
        // if item is withing 300 range and energy is over 75, walk to the item
        if(abs(_positionComponent->X - itemPosition->X) < 150 &&  abs(_positionComponent->Y - itemPosition->Y) <= 64 && _turnComponent->getEnergy() > 75){
            _aiComponent->setCurrentState(std::make_unique<WanderState>(*_entityManager, _entityId, *itemPosition, *_entityManager->getComponentFromEntity<DamageableComponent>(iterator.first), *_context));
            return;
        }
    }*/
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
        if(iterator.first == _entityId) continue;
        auto targetPosition = _entityManager->getComponentFromEntity<PositionComponent>(iterator.first);
        if(_previousState == "attackstate" && distanceToEnemy <= 700)
        {
            PositionComponent target{0, targetPosition->Y};
            target.X = targetPosition->X + (800 - _boxCollider->width);
            _aiComponent->setCurrentState(std::make_unique<WanderState>(*_entityManager, _entityId, *targetPosition, *_entityManager->getComponentFromEntity<DamageableComponent>(iterator.first), *_context));
        }
        // Far away, move to enemy
        else if(distanceToEnemy > 700) {
            PositionComponent target{0, targetPosition->Y};
            if(targetPosition->X < _positionComponent->X) target.X = targetPosition->X + (700 - _boxCollider->width);
            if(targetPosition->X > _positionComponent->X) target.X = targetPosition->X - (700 - _boxCollider->width);
            // Walk towards enemy
            _aiComponent->setCurrentState(std::make_unique<WanderState>(*_entityManager, _entityId, *targetPosition, *_entityManager->getComponentFromEntity<DamageableComponent>(iterator.first), *_context));
        } else if(iterator.second->getSelectedWeaponAvailability() > 0) {

            // try shooting
            // cant hit?
            // walk a bit towards or away from enemy
            auto playerComponent = _entityManager->getComponentFromEntity<PlayerComponent>(iterator.first);
            Weapon* selectedWeapon = playerComponent->getSelectedWeapon();
            for(int i = playerComponent->getAmountOFWeapons(); i > 0; i--){
                selectedWeapon = playerComponent->getSelectedWeapon();
                if(selectedWeapon->getAmmo() > 0) break;
                playerComponent->setSelectedWeapon("next");
            }

            // todo: search for weapon crate and set as target
            //if(selectedWeapon->getAmmo() <= 0) _aiComponent->setCurrentState(std::make_unique<WanderState>(*_entityManager, _entityId, target, *_context));

            // Attack state
            _aiComponent->setCurrentState(
                    std::make_unique<AttackState>(*_entityManager, _entityId, iterator.first, *targetPosition, *_entityManager->getComponentFromEntity<DamageableComponent>(iterator.first), *_context));
        }
        return;
    }
}

// returns closest item Id within 150x and 64y range
int IdleState::getClosestItem(){
    int closestItem = -1;
    for(const auto& iterator: _entityManager->getAllEntitiesWithComponent<ItemComponent>()) {
        auto itemPosition = _entityManager->getComponentFromEntity<PositionComponent>(iterator.first);
        if(abs(_positionComponent->X - itemPosition->X) < 150 &&  abs(_positionComponent->Y - itemPosition->Y) <= 64 && _turnComponent->getEnergy() > 75) {
            if(closestItem == -1) closestItem = iterator.first;
            else if(abs(_positionComponent->X - itemPosition->X) < abs(_positionComponent->X - _entityManager->getComponentFromEntity<PositionComponent>(closestItem)->X)) {
                closestItem = iterator.first;
            }
        }
    }
    return closestItem;
}

// returns manhattan distance to enemy
double IdleState::getDistanceToEnemy(){
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
        if (iterator.first == _entityId) continue;
        auto targetPosition = _entityManager->getComponentFromEntity<PositionComponent>(iterator.first);
        return abs(_positionComponent->X - targetPosition->X) + abs(_positionComponent->Y - targetPosition->Y);
    }
    return -1;
}

// returns the total amount of ammo
int IdleState::getAmountOfAmmo(){
    auto playerComponent = _entityManager->getComponentFromEntity<PlayerComponent>(_entityId);
    Weapon *selectedWeapon = playerComponent->getSelectedWeapon();
    int amountOfAmmo = 0;
    for (int i = playerComponent->getAmountOFWeapons(); i > 0; i--) {
        selectedWeapon = playerComponent->getSelectedWeapon();
        amountOfAmmo += selectedWeapon->getAmmo();
        playerComponent->setSelectedWeapon("next");
    }
    return amountOfAmmo;
}

// Returns the enemy players health
int IdleState::getEnemyHealth(){
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
        if (iterator.first == _entityId) continue;
        return _entityManager->getComponentFromEntity<DamageableComponent>(iterator.first)->getHealth();
    }
    return -1;
}