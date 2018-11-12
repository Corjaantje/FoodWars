#include "../../../Headers/GameECS/Systems/AnimationSystem.h"
#include "../../../Headers/GameECS/Components/AnimationComponent.h"
#include "../../../Headers/GameECS/Components/PositionComponent.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"

AnimationSystem::AnimationSystem(std::shared_ptr<EntityManager> entityManager) {
    _entityManager = std::move(entityManager);
}

void AnimationSystem::update(double deltatime) {
    // Get all animating entities
    for(const auto& iterator:_entityManager->getAllEntitiesWithComponent<AnimationComponent>())
    {
        iterator.second->setElapsedTime(iterator.second->getElapsedTime() + deltatime);
        if(iterator.second->getElapsedTime() >= iterator.second->getAnimationInterval())
        {
            // Go to next image
            if(iterator.second->getCurrentShapeIndex() >= iterator.second->getNumberOfAnimationShapes() - 1)
                iterator.second->setCurrentShapeIndex(0);
            else
                iterator.second->setCurrentShapeIndex(iterator.second->getCurrentShapeIndex() + 1);

            iterator.second->setElapsedTime(0);
        }
        std::shared_ptr<DrawableComponent> drawableComponent = _entityManager->getComponentFromEntity<DrawableComponent>(iterator.first);
        drawableComponent->shape = iterator.second->getCurrentShape();
    }
}
