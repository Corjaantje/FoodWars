#include <utility>

#include "../../../Headers/GameECS/Systems/MoveSystem.h"
#include "../../../Headers/GameECS/Components/MoveComponent.h"
#include "../../../Headers/GameECS/Components/TurnComponent.h"
#include "../../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../../Headers/GameECS/Components/PlayerComponent.h"
#include "../../../Headers/GameECS/Components/AIComponent.h"
#include <cmath>

MoveSystem::~MoveSystem() {
    delete autoClimbOnCollision;
}

MoveSystem::MoveSystem(EntityManager &entityManager, InputFacade& inputFacade,
                       IObservable<CollisionEvent> &collisionEventObservable) :
        _entityManager{&entityManager},
        _pressedKey{KEY::KEY_OTHER} {
    inputFacade.getKeyEventObservable().registerKeyEventObserver(this);
    autoClimbOnCollision  = new CollisionEventHandlerLamda {
        collisionEventObservable,
        // Staircase walking
        /*[entityManager = _entityManager](const CollisionEvent& collisionEvent) {
            double angle = collisionEvent.getCollisionAngle();
            return (angle >= 45 && angle <= 135) || (angle >= 225 && angle <= 315);
        } ,*/
        [](const CollisionEvent& collisionEvent){
            return false;
        },
        [entityManager = _entityManager](const CollisionEvent& collisionEvent) {
            auto *moveComponent = entityManager->getComponentFromEntity<MoveComponent>(collisionEvent.getEntity());
            auto *boxCollider = entityManager->getComponentFromEntity<BoxCollider>(collisionEvent.getEntity());
            auto *positionComponent = entityManager->getComponentFromEntity<PositionComponent>(
                    collisionEvent.getEntity());
            auto *otherPositionComponent = entityManager->getComponentFromEntity<PositionComponent>(
                    collisionEvent.getOtherEntity());
            if(std::abs(positionComponent->Y + boxCollider->height/2) < otherPositionComponent->Y) {
                //moveComponent->yVelocity = 0;
                positionComponent->Y = otherPositionComponent->Y - boxCollider->height;
            }
        }
    };
}

void MoveSystem::update(double dt) {
    const int walkingEnergyCostPerSecond = 20;
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
        if(_entityManager->getComponentFromEntity<AIComponent>(iterator.first)) continue;
        auto *moveComponent = _entityManager->getComponentFromEntity<MoveComponent>(iterator.first);
        auto *turnComponent = _entityManager->getComponentFromEntity<TurnComponent>(iterator.first);
        double energy = turnComponent->getEnergy();
        if (energy - (walkingEnergyCostPerSecond * dt) <= 0) {
            moveComponent->xVelocity = 0;
            break;
        }
        if (turnComponent->isMyTurn()) {
            if (_pressedKey == KEY::KEY_A) {
                moveComponent->xVelocity = -100;
                turnComponent->lowerEnergy(walkingEnergyCostPerSecond * dt);
            }
            else if (_pressedKey == KEY::KEY_D) {
                moveComponent->xVelocity = 100;
                turnComponent->lowerEnergy(walkingEnergyCostPerSecond * dt);
            }else
                moveComponent->xVelocity = 0;
        } else {
            moveComponent->xVelocity = 0;
        }
    }

    for (auto const &iterator: _entityManager->getAllEntitiesWithComponent<MoveComponent>()) {
        auto *moveComponent = iterator.second;
        auto *positionComponent = _entityManager->getComponentFromEntity<PositionComponent>(iterator.first);
        if(positionComponent) {
            positionComponent->X += std::round(dt * moveComponent->xVelocity);
            positionComponent->Y += std::round(dt * moveComponent->yVelocity);
        }
    }
}

void MoveSystem::update(const KeyEvent& event) {
    if(event.getKeyEventType() == KeyEventType::Up && event.getKey() == _pressedKey) {
        _pressedKey = KEY::KEY_OTHER;
    } else if(event.getKeyEventType() == KeyEventType::Down && (event.getKey() == KEY::KEY_A || event.getKey() == KEY::KEY_D)) {
        _pressedKey = event.getKey();
    }
}
