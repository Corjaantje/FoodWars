#include <utility>

#include <utility>

#include <iostream>
#include "../../Headers/AI/IdleState.h"
#include "../../Headers/AI/WanderState.h"
#include "../../Headers/AI/AttackState.h"
#include "../../Headers/GameECS/Components/ItemComponent.h"
#include <math.h>

IdleState::IdleState(EntityManager &entityManager, int entityId, AISystem &context) : State(entityManager, entityId,
                                                                                            context) {

}

void IdleState::enter() {
    std::cout << "Entering idle state" << std::endl;
    _enemyId = getEnemyId();
}

void IdleState::execute(double dt) {
    // Stop walking
    _moveComponent->xVelocity = 0;

    /** if in shooting range & kogels:
     *      distance to powerup < 80 om op te pakken ander schieten
     *  distance to power < 400
     *      pak powerup
     */

    // if my turn, calculate new state

    _playerCenterX = static_cast<int>(std::round(_positionComponent->X + _boxCollider->width / 2.0));
    _playerCenterY = static_cast<int>(std::round(_positionComponent->Y + _boxCollider->height / 2.0));

    if(_turnComponent->isMyTurn() && _turnComponent->getRemainingTime() > 0 && _turnComponent->getEnergy() > 0.0) {
        chooseState();
    }
}

void IdleState::exit() {

}


void IdleState::chooseState(){
    // Get necessary variables
    int closestItem = getClosestItem();
    double distanceToEnemy = getDistanceToPoint(_enemyId);
    int amountOfAmmo = getAmountOfAmmo();
    double energy = _entityManager->getComponentFromEntity<TurnComponent>(_entityId)->getEnergy();
    int myHealth = _entityManager->getComponentFromEntity<DamageableComponent>(_entityId)->getHealth();
    int enemyHealth = getEnemyHealth();


    /*std::cout << "closestItem: " << closestItem << std::endl;
    std::cout << "distanceToEnemy: " << distanceToEnemy << std::endl;
    std::cout << "amountOfAmmo: " << amountOfAmmo << std::endl;
    std::cout << "energy: " << energy << std::endl;
    std::cout << "myHealth: " << myHealth << std::endl;
    std::cout << "enemyHealth: " << enemyHealth << std::endl;*/

    if (!_entityManager->getComponentFromEntity<PlayerComponent>(_enemyId)->isAlive())
        return;

    // Out of ammo
    if ((amountOfAmmo <= 0 && closestItem > 0) || (closestItem > 0 && getDistanceToPoint(closestItem) < 96)) {
        std::cout << "Out of ammo, grabbing item" << std::endl;
        auto itemPosition = _entityManager->getComponentFromEntity<PositionComponent>(closestItem);
        auto itemCollider = _entityManager->getComponentFromEntity<BoxCollider>(closestItem);
        int itemCenterX = static_cast<int>(itemPosition->X + itemCollider->width / 2.0);
        int itemCenterY = static_cast<int>(itemPosition->Y + itemCollider->height / 2.0);
        PositionComponent centerItemPosition{itemCenterX, itemCenterY};
        _aiComponent->setCurrentState(
                std::make_unique<WanderState>(*_entityManager, _entityId, centerItemPosition, nullptr, *_context));
        return;
    }
    // Within 700 range
    else if (distanceToEnemy <= _maxShootingRange + _boxCollider->height) {
        // Enough ammo and energy to shoot enemy
        if(amountOfAmmo > 0 && energy >= 20) {
            std::cout << "Attacking enemy" << std::endl;
            auto targetPosition = _entityManager->getComponentFromEntity<PositionComponent>(_enemyId);
            _aiComponent->setCurrentState(
                    std::make_unique<AttackState>(*_entityManager, _entityId, _enemyId, *targetPosition,
                                                  *_entityManager->getComponentFromEntity<DamageableComponent>(
                                                          _enemyId), *_context));
            return;
        }
        // Already attacked so < 20 energy
            /*else if(_previousState == "attackstate"){
                // Cant do much, try walking to the closest item
                if(closestItem > 0){
                    std::cout << "Tired, grabbing item" << std::endl;
                    _aiComponent->setCurrentState(std::make_unique<WanderState>(*_entityManager, _entityId, *_entityManager->getComponentFromEntity<PositionComponent>(closestItem), nullptr, *_context));
                    return;
                }
                // Cant do anything, set energy to 0
                else{
                    std::cout << "Tired, set energy to 0" << std::endl;
                    _turnComponent->setEnergy(0);
                }
            }*/

        else if (closestItem > 0) { // walk to closest item
            std::cout << "Not enough energy to shoot, walking to nearest item" << std::endl;
            auto itemPosition = _entityManager->getComponentFromEntity<PositionComponent>(closestItem);
            auto itemCollider = _entityManager->getComponentFromEntity<BoxCollider>(closestItem);
            int itemCenterX = static_cast<int>(itemPosition->X + itemCollider->width / 2.0);
            int itemCenterY = static_cast<int>(itemPosition->Y + itemCollider->height / 2.0);
            PositionComponent centerItemPosition{itemCenterX, itemCenterY};
            _aiComponent->setCurrentState(
                    std::make_unique<WanderState>(*_entityManager, _entityId, centerItemPosition, nullptr, *_context));
            return;
        }
            // Cant do anything, run away from enemy
        else {
            /*_turnComponent->setEnergy(0);*/
            flee();
            return;
        }
    }
    // Over 700 range from enemy
    else if (distanceToEnemy > _maxShootingRange) {
        // If item is within walking distance, 32 being a tile size, 4 being the energy spent walking per tile
        if (closestItem > 0 && energy >= getDistanceToPoint(closestItem) / 32 * 5) {
            std::cout << "Far away, grabbing item" << std::endl;
            auto itemPosition = _entityManager->getComponentFromEntity<PositionComponent>(closestItem);
            _aiComponent->setCurrentState(std::make_unique<WanderState>(*_entityManager, _entityId, *itemPosition, nullptr , *_context));
            return;
        }
        // Walk towards enemy
        else if (amountOfAmmo > 0) {
            std::cout << "Far away, walking towards enemy" << std::endl;
            auto targetPosition = _entityManager->getComponentFromEntity<PositionComponent>(_enemyId);
            PositionComponent target{0, -1};
            if (targetPosition->X < _positionComponent->X) target.X = targetPosition->X +
                                                                      (_maxShootingRange - _boxCollider->width);
            else if (targetPosition->X > _positionComponent->X)
                target.X = targetPosition->X -
                           (_maxShootingRange - _boxCollider->width);

            if (targetPosition->Y < _positionComponent->Y) { //target staat boven player
                if (targetPosition->X < _positionComponent->X) target.X -= _positionComponent->Y - targetPosition->Y;
                else if (targetPosition->X > _positionComponent->X)
                    target.X += _positionComponent->Y - targetPosition->Y;
            }
            _aiComponent->setCurrentState(
                    std::make_unique<WanderState>(*_entityManager, _entityId, target, nullptr, *_context));
            return;
        } else {
            flee();
            return;
        }
    }
}

// returns closest item Id within 150x and 64y range
int IdleState::getClosestItem(){
    int closestItem = -1;
    double closestItemDistance = 1600;
    for(const auto& iterator: _entityManager->getAllEntitiesWithComponent<ItemComponent>()) {
        auto itemPosition = _entityManager->getComponentFromEntity<PositionComponent>(iterator.first);
        auto itemCollider = _entityManager->getComponentFromEntity<BoxCollider>(iterator.first);
        double itemCenterX = itemPosition->X + itemCollider->width / 2.0;
        double itemCenterY = itemPosition->Y + itemCollider->height / 2.0;
        double yDiff = itemCenterY - _playerCenterY;
        if (yDiff < -45) continue; // item ligt boven de speler
        double distance = abs(_playerCenterX - itemCenterX) + yDiff;
        if (distance < closestItemDistance) {
            closestItem = iterator.first;
            closestItemDistance = distance;
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
    return _entityManager->getComponentFromEntity<DamageableComponent>(_enemyId)->getHealth();
}

int IdleState::getEnemyId() {
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
        if (iterator.first == _entityId) continue;
        return iterator.first;
    }
    return -1;
}

void IdleState::flee() {
    auto targetPosition = _entityManager->getComponentFromEntity<PositionComponent>(_enemyId);
    PositionComponent target{0, -1};
    if (targetPosition->X > _positionComponent->X) //target rechts van speler
        target.X = _boxCollider->width / 2.0;
    else
        target.X = 1600 - (_boxCollider->width + _boxCollider->width / 2.0);

    std::cout << "Tired, fleeing to: " << target.X << std::endl;
    if (abs(_positionComponent->X - target.X) < _boxCollider->width) {
        _turnComponent->setEnergy(0);
        return;
    }
    _aiComponent->setCurrentState(
            std::make_unique<WanderState>(*_entityManager, _entityId, target, nullptr, *_context));
}
