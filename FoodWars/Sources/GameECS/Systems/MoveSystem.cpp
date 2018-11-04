#include <utility>

#include "../../../Headers/GameECS/Systems/MoveSystem.h"
#include "../../../Headers/GameECS/Components/MoveComponent.h"
#include "../../../Headers/GameECS/Components/TurnComponent.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../../Headers/GameECS/Events/CollisionEventHandlerLamda.h"
#include <cmath>

MoveSystem::~MoveSystem() {
    delete trapWalkOnCollision;
}

MoveSystem::MoveSystem(std::shared_ptr<EntityManager> entityManager, std::shared_ptr<InputFacade> inputFacade, IObservable<CollisionEvent>& collisionEventObservable) {
    _entityManager = std::move(entityManager);
    inputFacade->getKeyEventObservable()->registerKeyEventObserver(this);
    trapWalkOnCollision  = new CollisionEventHandlerLamda {
        collisionEventObservable,
        [entityManager = _entityManager](const CollisionEvent& collisionEvent) {
            double angle = collisionEvent.getCollisionAngle();
            return (angle >= 45 && angle <= 135) || (angle >= 225 && angle <= 315);
        } ,
        [entityManager = _entityManager](const CollisionEvent& collisionEvent) {
            std::shared_ptr<MoveComponent> moveComponent = entityManager->getComponentFromEntity<MoveComponent>(collisionEvent.getEntity());
            std::shared_ptr<BoxCollider> boxCollider = entityManager->getComponentFromEntity<BoxCollider>(collisionEvent.getEntity());
            std::shared_ptr<PositionComponent> positionComponent = entityManager->getComponentFromEntity<PositionComponent>(collisionEvent.getEntity());
            std::shared_ptr<PositionComponent> otherPositionComponent = entityManager->getComponentFromEntity<PositionComponent>(collisionEvent.getOtherEntity());
            if(std::abs(positionComponent->Y + boxCollider->height/2) < otherPositionComponent->Y) {
                //moveComponent->yVelocity = 0;
                positionComponent->Y = otherPositionComponent->Y - boxCollider->height;
            }
        }
    };
}

void MoveSystem::update(double dt) {
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<TurnComponent>()) {
        std::shared_ptr<MoveComponent> moveComponent = _entityManager->getComponentFromEntity<MoveComponent>(iterator.first);
        if (iterator.second->isMyTurn()) {
            if (_pressedKey == KEY::KEY_A) {
                moveComponent->xVelocity = -100;
            } else if (_pressedKey == KEY::KEY_D) {
                moveComponent->xVelocity = 100;
            } else
                moveComponent->xVelocity = 0;
        } else {
            moveComponent->xVelocity = 0;
        }
    }

    for (auto const &iterator: _entityManager->getAllEntitiesWithComponent<MoveComponent>()) {
        int entity = iterator.first;
        std::shared_ptr<MoveComponent> moveComponent = iterator.second;
        std::shared_ptr<PositionComponent> positionComponent = _entityManager->getComponentFromEntity<PositionComponent>(iterator.first);
        if(positionComponent) {
            positionComponent->X += std::round(dt * moveComponent->xVelocity);
            positionComponent->Y += std::round(dt * moveComponent->yVelocity);
        }
    }
}

void MoveSystem::update(std::shared_ptr<KeyEvent> event) {
    if(event->getKeyEventType() == KeyEventType::Up && event->getKey() == _pressedKey) {
        _pressedKey = KEY::KEY_OTHER;
    } else if(event->getKeyEventType() == KeyEventType::Down && (event->getKey() == KEY::KEY_A || event->getKey() == KEY::KEY_D)) {
        _pressedKey = event->getKey();
    }
}
