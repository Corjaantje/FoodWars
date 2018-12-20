#include "../../../Headers/GameECS/Systems/AnimationSystem.h"
#include "../../../Headers/GameECS/Components/PlayerComponent.h"
#include "../../../Headers/GameECS/Components/AIComponent.h"

AnimationSystem::AnimationSystem(EntityManager &entityManager)
        : _entityManager(&entityManager), _animationManager(AnimationManager{})
{
}

void AnimationSystem::update(double deltatime) {
    // Edit player animations based on movement
    for (const auto &iterator: _entityManager->getAllEntitiesWithComponent<TurnComponent>()) {
        Faction faction = _entityManager->getComponentFromEntity<PlayerComponent>(iterator.first)->getFaction();
        auto *moveComponent = _entityManager->getComponentFromEntity<MoveComponent>(iterator.first);
        auto *positionComponent = _entityManager->getComponentFromEntity<PositionComponent>(iterator.first);
        auto *boxCollider = _entityManager->getComponentFromEntity<BoxCollider>(iterator.first);
        auto *animationComponent = _entityManager->getComponentFromEntity<AnimationComponent>(iterator.first);

        // Set animations for movement and direction
        if (moveComponent->xVelocity < 0 &&
            (!animationComponent->getIsLookingLeft() || animationComponent->getIsIdle())) { // Left
            animationComponent->setAnimationShapes(
                    _animationManager.moveLeftAnimation(boxCollider->width, boxCollider->height, positionComponent->X,
                                                         positionComponent->Y, faction));
            animationComponent->setIsLookingLeft(true);
            animationComponent->setIsIdle(false);
        } else if (moveComponent->xVelocity > 0 &&
                   (animationComponent->getIsLookingLeft() || animationComponent->getIsIdle())) { // Right
            animationComponent->setAnimationShapes(
                    _animationManager.moveRightAnimation(boxCollider->width, boxCollider->height, positionComponent->X,
                                                          positionComponent->Y, faction));
            animationComponent->setIsLookingLeft(false);
            animationComponent->setIsIdle(false);
        } else if (moveComponent->xVelocity == 0 && !animationComponent->getIsIdle()) { // Standing still
            if (animationComponent->getIsLookingLeft())
                animationComponent->setAnimationShapes(
                        _animationManager.lookLeftAnimation(boxCollider->width, boxCollider->height,
                                                             positionComponent->X, positionComponent->Y, faction));
            else
                animationComponent->setAnimationShapes(
                        _animationManager.lookRightAnimation(boxCollider->width, boxCollider->height,
                                                              positionComponent->X, positionComponent->Y, faction));
            animationComponent->setIsIdle(true);
        }
    }

    // Get all animating entities
    for (const auto &iterator:_entityManager->getAllEntitiesWithComponent<AnimationComponent>()) {
        iterator.second->setElapsedTime(iterator.second->getElapsedTime() + deltatime);
        if (iterator.second->getElapsedTime() >= iterator.second->getAnimationInterval()) {
            // Go to next image
            if (iterator.second->getCurrentShapeIndex() >= iterator.second->getNumberOfAnimationShapes() - 1)
                iterator.second->setCurrentShapeIndex(0);
            else
                iterator.second->setCurrentShapeIndex(iterator.second->getCurrentShapeIndex() + 1);

            iterator.second->setElapsedTime(0);
        }
        auto *drawableComponent = _entityManager->getComponentFromEntity<DrawableComponent>(iterator.first);
        auto *shape = dynamic_cast<ShapeSprite *>(iterator.second->getCurrentShape());
        if (shape) {
            drawableComponent->setShape(
                    std::make_unique<ShapeSprite>(shape->getWidth(), shape->getHeight(), shape->xPos, shape->yPos,
                                                  shape->imageURL, shape->layer));
        }
    }
}