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
            _entityManager->addComponentToEntity(iterator.first, new MoveComponent(iterator.second->gravityApplied));
        } else {
            moveComponent->yVelocity += std::pow(iterator.second->gravityApplied, 2.5) * dt;
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
}
