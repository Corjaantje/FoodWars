#include <utility>
#include <cmath>
#include "../../../Headers/GameECS/Systems/GravitySystem.h"
#include "../../../Headers/GameECS/Components/GravityComponent.h"
#include "../../../Headers/GameECS/Components/MoveComponent.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../Headers/GameECS/Components/TurnComponent.h"
#include "../../../Headers/GameECS/Components/Collider/BoxCollider.h"

GravitySystem::~GravitySystem() = default;

GravitySystem::GravitySystem(std::shared_ptr<EntityManager> entityManager, IObservable<CollisionEvent>& collisionEventObservable) : CollisionEventHandler(collisionEventObservable), _entityManager(std::move(entityManager)) {

}

void GravitySystem::update(double dt) {
    for(auto const &iterator: _entityManager->getAllEntitiesWithComponent<GravityComponent>()) {
        std::shared_ptr<MoveComponent> moveComponent = _entityManager->getComponentFromEntity<MoveComponent>(iterator.first);
        if(!moveComponent) {
            _entityManager->addComponentToEntity(iterator.first, new MoveComponent(PositionComponent(0, 1),
                                                                                   iterator.second->gravityApplied));
        } else {
           // moveComponent->positionComponent += PositionComponent{0, 1};
            moveComponent->yVelocity += iterator.second->gravityApplied;
        }
    }
}

bool GravitySystem::canHandle(const CollisionEvent &collisionEvent) {
    return (collisionEvent.getCollisionAngle() >= 270 || collisionEvent.getCollisionAngle() <= 90) && _entityManager->getComponentFromEntity<TurnComponent>(collisionEvent.getEntity()) != nullptr;
}

void GravitySystem::handleCollisionEvent(const CollisionEvent &collisionEvent) {
    std::shared_ptr<MoveComponent> moveComponent = _entityManager->getComponentFromEntity<MoveComponent>(collisionEvent.getEntity());
    std::shared_ptr<BoxCollider> boxCollider = _entityManager->getComponentFromEntity<BoxCollider>(collisionEvent.getEntity());
    std::shared_ptr<PositionComponent> positionComponent = _entityManager->getComponentFromEntity<PositionComponent>(collisionEvent.getEntity());
    moveComponent->yVelocity = 0;
    /*double angle = collisionEvent.getCollisionAngle();
    if( angle > 315 || angle < 45 ) {
        std::shared_ptr<PositionComponent> otherPositionComponent = _entityManager->getComponentFromEntity<PositionComponent>(collisionEvent.getOtherEntity());
        positionComponent->Y = otherPositionComponent->Y - boxCollider->height;
    }*/
    /*std::shared_ptr<GravityComponent> gravityComponent = _entityManager->getComponentFromEntity<GravityComponent>(collisionEvent.getEntity());
    if(gravityComponent)
        _entityManager->removeComponentFromEntity<GravityComponent>(collisionEvent.getEntity());*/
}
