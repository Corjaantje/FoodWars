#include "../../../Headers/GameECS/Systems/CollisionSystem.h"
#include "../../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../../Headers/GameECS/Components/MoveComponent.h"
#include <cmath>

CollisionSystem::CollisionSystem(std::shared_ptr<EntityManager> entityManager) : _entityManager(entityManager) {

}

void CollisionSystem::update(double dt) {
    std::map<int, std::shared_ptr<BoxCollider>> entitiesWithCollider = _entityManager->getAllEntitiesWithComponent<BoxCollider>();

    for(auto const &iterator: _entityManager->getAllEntitiesWithComponent<MoveComponent>()) {
        int entity = iterator.first;
        std::shared_ptr<BoxCollider> collider = entitiesWithCollider[entity];
        if(!collider)
            continue;
        std::shared_ptr<MoveComponent> moveComponent = iterator.second;
        std::shared_ptr<PositionComponent> positionComponent = _entityManager->getComponentFromEntity<PositionComponent>(entity);
        if(positionComponent && (std::abs(moveComponent->xVelocity) > 0 || std::abs(moveComponent->yVelocity) > 0)) {
            for (auto const &collideAbleIterator : entitiesWithCollider) {
                int otherEntity = collideAbleIterator.first;
                if (otherEntity == entity)
                    continue;
                std::shared_ptr<BoxCollider> otherCollider = collideAbleIterator.second;
                std::shared_ptr<PositionComponent> otherPosition = _entityManager->getComponentFromEntity<PositionComponent>(otherEntity);
                if (positionComponent) {
                    bool willCollide = positionComponent->X < otherPosition->X + otherCollider->width &&
                                  positionComponent->X + collider->width > otherPosition->X &&
                                  positionComponent->Y < otherPosition->Y + otherCollider->height &&
                                  positionComponent->Y + collider->height > otherPosition->Y;
                    if(willCollide) {
                        if(positionComponent->Y + collider->height > otherPosition->Y) {
                            std::cout << "Collide bottom top" << std::endl;
                            notify(std::make_shared<CollisionEvent>(CollisionEvent{entity, Direction::Bottom, otherEntity, Direction::Top}));
                        } else {
                            std::cout << "Collide other" << std::endl;
                            notify(std::make_shared<CollisionEvent>(
                                    CollisionEvent{entity, Direction::Right, otherEntity, Direction::Right}));
                        }



                        /*if(ballPosition.y >= brickPosition.y + (brickHeight/2))
                            //Hit was from above the brick

                            if(ballPostion.x < brickPosition.x)
                                //Hit was on left

                                if(ballPostion.x > brickPosition.x)*/
                        /* if (moveComponent->positionComponent.X > 0) {
                             drawableComponent->shape->xPos = otherDrawable->shape->xPos - collider->width;
                         }
                         if (moveComponent->positionComponent.Y > 0 && (drawableComponent->shape->yPos - collider->height) != newY) {
                             drawableComponent->shape->yPos = otherDrawable->shape->yPos - collider->height;
                         }*/
                        break;
                    }
                }
            }
        }
    }
}

