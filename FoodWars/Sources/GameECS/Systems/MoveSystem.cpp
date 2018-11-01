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
    _keyEventObservable = inputFacade->getKeyEventObservable();
    //inputFacade->getKeyEventObservable()->registerKeyPressedMapObserver(this);
    inputFacade->getKeyEventObservable()->registerKeyEventObserver(this);
    /*trapWalkOnCollision  = new CollisionEventHandlerLamda {
        collisionEventObservable,
        [entityManager = _entityManager](const CollisionEvent& collisionEvent) {
            return (collisionEvent.getEntityDirection() == Direction::Left || collisionEvent.getEntityDirection() == Direction::Right); //&&
        } ,
        [entityManager = _entityManager](const CollisionEvent& collisionEvent) {
            std::shared_ptr<MoveComponent> moveComponent = entityManager->getComponentFromEntity<MoveComponent>(collisionEvent.getEntity());
            std::shared_ptr<BoxCollider> boxCollider = entityManager->getComponentFromEntity<BoxCollider>(collisionEvent.getEntity());
            std::shared_ptr<PositionComponent> positionComponent = entityManager->getComponentFromEntity<PositionComponent>(collisionEvent.getEntity());
            std::shared_ptr<PositionComponent> otherPositionComponent = entityManager->getComponentFromEntity<PositionComponent>(collisionEvent.getOtherEntity());
            if(std::abs(positionComponent->Y - otherPositionComponent->Y - boxCollider->height) <= boxCollider->height/2) {
                moveComponent->yVelocity = 0;
                positionComponent->Y = otherPositionComponent->Y - boxCollider->height;
            }
        }
    };*/
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
/*
        moveComponent->positionComponent--;
        if(moveComponent->xVelocity < 0 && moveComponent->yVelocity < 0)
            _entityManager->removeComponentFromEntity<MoveComponent>(entity);*/
    }
}

void MoveSystem::update(std::shared_ptr<KeyEvent> event) {
    if(event->getKeyEventType() == KeyEventType::Up && event->getKey() == _pressedKey) {
        std::cout << "Key unpressed" << std::endl;
        _pressedKey = KEY::KEY_OTHER;
    } else if(event->getKeyEventType() == KeyEventType::Down && (event->getKey() == KEY::KEY_A || event->getKey() == KEY::KEY_D)) {
        std::cout << "Key pressed" << std::endl;
        _pressedKey = event->getKey();
    }
}

/*void MoveSystem::update(std::shared_ptr<std::map<KEY, bool>> event) {
    std::cout << "pressed keys changed" << std::endl;
    _pressedKeys = *event.get();
}*/
/*

void MoveSystem::update(std::shared_ptr<KeyEvent> event) {
    std::cout << "Key event: ";
    MoveComponent moveComponent;

    if(event->getKeyEventType() == KeyEventType::Up) {
        _pressedKeys.erase(_pressedKeys.begin(), _pressedKeys.end(), )
    }

    switch(event->getKeyEventType()) {
        case KeyEventType::Up:
            std::cout << "Up: ";
            break;
        case KeyEventType::Down:
            std::cout << "Down: ";
            break;
    }
    switch (event->getKey()) {
        case KEY::KEY_W:
            std::cout << "W" << std::endl;
            moveComponent.positionComponent = PositionComponent{0, -100};
            break;
        case KEY::KEY_A:
            std::cout << "A" << std::endl;
            moveComponent.positionComponent = PositionComponent{-10, 0};
            break;
        case KEY::KEY_D:
            std::cout << "D" << std::endl;
            moveComponent.positionComponent = PositionComponent{10, 0};
            break;
        case KEY::KEY_S:
            std::cout << "S" << std::endl;
            moveComponent.positionComponent = PositionComponent{0, 10};
            break;
        default:
            break;
    }

    for(auto const& iterator: _entityManager->getAllEntitiesWithComponent<TurnComponent>()){
        std::shared_ptr<TurnComponent> turnComponent = iterator.second;
        if(turnComponent->isMyTurn()){
            std::shared_ptr<MoveComponent> entityMoveComponent = _entityManager->getComponentFromEntity<MoveComponent>(iterator.first);
            if(entityMoveComponent) {
                entityMoveComponent->xVelocity = 10;
                entityMoveComponent->yVelocity = 10;
                entityMoveComponent->positionComponent += moveComponent.positionComponent;
            } else
                _entityManager->addComponentToEntity(iterator.first, new MoveComponent(moveComponent.positionComponent, 10));
        }
    }
}
*/
