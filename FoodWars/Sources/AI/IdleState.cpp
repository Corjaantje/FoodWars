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
    // Get necessary variables
    int enemyId = getEnemyId();
    int closestItem = getClosestItem();
    double distanceToEnemy = getDistanceToPoint(enemyId);
    int amountOfAmmo = getAmountOfAmmo();
    double energy = _entityManager->getComponentFromEntity<TurnComponent>(_entityId)->getEnergy();
    int myHealth = _entityManager->getComponentFromEntity<DamageableComponent>(_entityId)->getHealth();
    int enemyHealth = getEnemyHealth();
    int maxShootingRange = 700;


    std::cout << "closestItem: " << closestItem << std::endl;
    /*std::cout << "distanceToEnemy: " << distanceToEnemy << std::endl;
    std::cout << "amountOfAmmo: " << amountOfAmmo << std::endl;
    std::cout << "energy: " << energy << std::endl;
    std::cout << "myHealth: " << myHealth << std::endl;
    std::cout << "enemyHealth: " << enemyHealth << std::endl;*/

    if(!_entityManager->getComponentFromEntity<PlayerComponent>(enemyId)->isAlive())
        return;

    // Out of ammo
    if((amountOfAmmo <= 0 && closestItem != -1) || getDistanceToPoint(closestItem) < 64){
        std::cout << "Out of ammo, grabbing item" << std::endl;
        auto itemPosition = _entityManager->getComponentFromEntity<PositionComponent>(closestItem);
        _aiComponent->setCurrentState(std::make_unique<WanderState>(*_entityManager, _entityId, *itemPosition, nullptr , *_context));
        return;
    }
    // Within 700 range
    else if(distanceToEnemy <= maxShootingRange) {
        // Enough ammo and energy to shoot enemy
        if(amountOfAmmo > 0 && energy >= 20) {
            std::cout << "Attacking enemy" << std::endl;
            auto targetPosition = _entityManager->getComponentFromEntity<PositionComponent>(enemyId);
            _aiComponent->setCurrentState(std::make_unique<AttackState>(*_entityManager, _entityId, enemyId, *targetPosition, *_entityManager->getComponentFromEntity<DamageableComponent>(enemyId), *_context));
            return;
        }
        // Already attacked so < 20 energy
        else if(_previousState == "attackstate"){
            // Cant do much, try walking to the closest item
            if(closestItem != -1){
                std::cout << "Tired, grabbing item" << std::endl;
                _aiComponent->setCurrentState(std::make_unique<WanderState>(*_entityManager, _entityId, *_entityManager->getComponentFromEntity<PositionComponent>(closestItem), nullptr, *_context));
                return;
            }
            // Cant do anything, set energy to 0
            else{
                std::cout << "Tired, set energy to 0" << std::endl;
                _turnComponent->setEnergy(0);
            }
        }
        // Cant do anything, run away from enemy
        else{
            /*_turnComponent->setEnergy(0);*/
            auto targetPosition = _entityManager->getComponentFromEntity<PositionComponent>(enemyId);
            PositionComponent target{0, targetPosition->Y};
            target.X = targetPosition->X + (maxShootingRange + 100 - _boxCollider->width);
            std::cout << "Tired, fleeing to: " << target.X << std::endl;
            _aiComponent->setCurrentState(std::make_unique<WanderState>(*_entityManager, _entityId, target, nullptr, *_context));
            return;
        }
    }
    // Over 700 range from enemy
    else if(distanceToEnemy > maxShootingRange) {
        // If item is within walking distance, 32 being a tile size, 4 being the energy spent walking per tile
        if(closestItem != -1 && energy >= getDistanceToPoint(closestItem) / 32 * 4){
            std::cout << "Far away, grabbing item" << std::endl;
            auto itemPosition = _entityManager->getComponentFromEntity<PositionComponent>(closestItem);
            _aiComponent->setCurrentState(std::make_unique<WanderState>(*_entityManager, _entityId, *itemPosition, nullptr , *_context));
            return;
        }
        // Walk towards enemy
        else{
            std::cout << "Far away, walking towards enemy" << std::endl;
            auto targetPosition = _entityManager->getComponentFromEntity<PositionComponent>(enemyId);
            PositionComponent target{0, targetPosition->Y};
            if(targetPosition->X < _positionComponent->X) target.X = targetPosition->X + (maxShootingRange - _boxCollider->width);
            if(targetPosition->X > _positionComponent->X) target.X = targetPosition->X - (maxShootingRange - _boxCollider->width);
            _aiComponent->setCurrentState(std::make_unique<WanderState>(*_entityManager, _entityId, *targetPosition, _entityManager->getComponentFromEntity<DamageableComponent>(enemyId), *_context));
            return;
        }
    }
}

// returns closest item Id within 150x and 64y range
int IdleState::getClosestItem(){
    int closestItem = -1;
    for(const auto& iterator: _entityManager->getAllEntitiesWithComponent<ItemComponent>()) {
        auto itemPosition = _entityManager->getComponentFromEntity<PositionComponent>(iterator.first);
        if(abs(_positionComponent->X - itemPosition->X) < 800 &&  abs(_positionComponent->Y - itemPosition->Y) <= 150) {
            if(closestItem == -1) closestItem = iterator.first;
            else if(abs(_positionComponent->X - itemPosition->X) < abs(_positionComponent->X - _entityManager->getComponentFromEntity<PositionComponent>(closestItem)->X)) {
                closestItem = iterator.first;
            }
        }
    }
    return closestItem;
}

// returns manhattan distance to a point
double IdleState::getDistanceToPoint(int target){
    auto targetPosition = _entityManager->getComponentFromEntity<PositionComponent>(target);
    auto targetBoxCollider = _entityManager->getComponentFromEntity<BoxCollider>(target);

    double playerCenterX = _positionComponent->X + _boxCollider->width / 2.0;
    double playerCenterY = _positionComponent->Y + _boxCollider->height / 2.0;
    double targetCenterX = targetPosition->X + targetBoxCollider->width / 2.0;
    double targetCenterY = targetPosition->Y + targetBoxCollider->height / 2.0;

    return abs(playerCenterX - targetCenterX) + abs(playerCenterY - targetCenterY);
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
    return _entityManager->getComponentFromEntity<DamageableComponent>(getEnemyId())->getHealth();
}

int IdleState::getEnemyId() {
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
        if (iterator.first == _entityId) continue;
        return iterator.first;
    }
    return -1;
}