#include "../../../Headers/GameECS/Systems/AnimationSystem.h"

AnimationSystem::AnimationSystem(EntityManager &entityManager, AnimationManager *animationManager)
        : _entityManager(&entityManager), _animationManager(animationManager) {
}

void AnimationSystem::update(double deltatime) {
    //TODO: Replace team by teamcomponent
    int team = 0;
    // Edit player animations based on movement
    for (const auto &iterator: _entityManager->getAllEntitiesWithComponent<TurnComponent>()) {
        auto *moveComponent = _entityManager->getComponentFromEntity<MoveComponent>(iterator.first);
        auto *positionComponent = _entityManager->getComponentFromEntity<PositionComponent>(iterator.first);
        auto *boxCollider = _entityManager->getComponentFromEntity<BoxCollider>(iterator.first);
        auto *animationComponent = _entityManager->getComponentFromEntity<AnimationComponent>(iterator.first);

        // Set animations for movement and direction
        if (moveComponent->xVelocity < 0 &&
            (!animationComponent->getIsLookingLeft() || animationComponent->getIsIdle())) { // Left
            animationComponent->setAnimationShapes(
                    _animationManager->moveLeftAnimation(boxCollider->width, boxCollider->height, positionComponent->X,
                                                         positionComponent->Y, team));
            animationComponent->setIsLookingLeft(true);
            animationComponent->setIsIdle(false);
        } else if (moveComponent->xVelocity > 0 &&
                   (animationComponent->getIsLookingLeft() || animationComponent->getIsIdle())) { // Right
            animationComponent->setAnimationShapes(
                    _animationManager->moveRightAnimation(boxCollider->width, boxCollider->height, positionComponent->X,
                                                          positionComponent->Y, team));
            animationComponent->setIsLookingLeft(false);
            animationComponent->setIsIdle(false);
        } else if (moveComponent->xVelocity == 0 && !animationComponent->getIsIdle()) { // Standing still
            if (animationComponent->getIsLookingLeft())
                animationComponent->setAnimationShapes(
                        _animationManager->lookLeftAnimation(boxCollider->width, boxCollider->height,
                                                             positionComponent->X, positionComponent->Y, team));
            else
                animationComponent->setAnimationShapes(
                        _animationManager->lookRightAnimation(boxCollider->width, boxCollider->height,
                                                              positionComponent->X, positionComponent->Y, team));
            animationComponent->setIsIdle(true);
        }
        // give p2 a different colour
        team++;
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