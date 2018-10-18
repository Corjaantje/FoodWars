#include <utility>

#include "../../../Headers/GameECS/Systems/MoveSystem.h"
#include "../../../Headers/GameECS/Components/MoveComponent.h"
#include "../../../Headers/GameECS/Components/TurnComponent.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../Headers/GameECS/Components/Collider/BoxCollider.h"

MoveSystem::~MoveSystem() = default;

MoveSystem::MoveSystem(std::shared_ptr<EntityManager> entityManager, std::shared_ptr<InputFacade> inputFacade) {
    _entityManager = std::move(entityManager);
    inputFacade->getKeyEventObservable()->registerObserver(this);
}

void MoveSystem::update(double dt) {
    std::map<int, std::shared_ptr<BoxCollider>> collideAbleEntities = _entityManager->getAllEntitiesWithComponent<BoxCollider>();
    for (auto const &iterator: _entityManager->getAllEntitiesWithComponent<MoveComponent>()) {
        int entity = iterator.first;
        std::shared_ptr<MoveComponent> moveComponent = iterator.second;
        std::shared_ptr<DrawableComponent> drawableComponent = _entityManager->getComponentFromEntity<DrawableComponent>(entity);
        std::shared_ptr<BoxCollider> collider = _entityManager->getComponentFromEntity<BoxCollider>(entity);

        double newX = drawableComponent->shape->xPos + moveComponent->positionComponent.X * dt * moveComponent->velocity;
        double newY = drawableComponent->shape->yPos + moveComponent->positionComponent.Y * dt * moveComponent->velocity;
        bool willCollide = false;

        if(collider) { // entity can collide so check for possible collision
            for (auto const &collideAbleIterator : collideAbleEntities) {
                int otherEntity = collideAbleIterator.first;
                if (otherEntity == entity)
                    continue;
                std::shared_ptr<BoxCollider> otherCollider = collideAbleIterator.second;
                std::shared_ptr<DrawableComponent> otherDrawable = _entityManager->getComponentFromEntity<DrawableComponent>(
                        otherEntity);
                if (otherDrawable) {
                    willCollide = newX < otherDrawable->shape->xPos + otherCollider->width &&
                                  newX + collider->width > otherDrawable->shape->xPos &&
                                  newY < otherDrawable->shape->yPos + otherCollider->height &&
                                  newY + collider->height > otherDrawable->shape->yPos;
                    if(willCollide)
                        break;
                }
            }
        }

        if(!willCollide){
            drawableComponent->shape->xPos = newX;
            drawableComponent->shape->yPos = newY;
        }

        moveComponent->velocity-=1;
        if(moveComponent->velocity < 0)
            _entityManager->removeComponentFromEntity<MoveComponent>(entity);
    }
}

void MoveSystem::update(std::shared_ptr<KeyEvent> event) {
    MoveComponent moveComponent;
    switch (event->getKey()) {
        case KEY::KEY_W:
            moveComponent.positionComponent = PositionComponent{0, -100};
            break;
        case KEY::KEY_A:
            moveComponent.positionComponent = PositionComponent{-10, 0};
            break;
        case KEY::KEY_D:
            moveComponent.positionComponent = PositionComponent{10, 0};
            break;
        case KEY::KEY_S:
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
                entityMoveComponent->velocity = 10;
                entityMoveComponent->positionComponent = moveComponent.positionComponent;
            } else
                _entityManager->addComponentToEntity(iterator.first, new MoveComponent(moveComponent.positionComponent, 10));
        }
    }
}
