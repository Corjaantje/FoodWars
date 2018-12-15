#include <utility>
#include <cmath>
#include "../../../Headers/GameECS/Systems/GravitySystem.h"
#include "../../../Headers/GameECS/Components/GravityComponent.h"
#include "../../../Headers/GameECS/Components/MoveComponent.h"
#include "../../../Headers/GameECS/Components/TurnComponent.h"

GravitySystem::~GravitySystem() = default;

GravitySystem::GravitySystem(EntityManager &entityManager, IObservable<CollisionEvent> &collisionEventObservable)
        : CollisionEventHandler(collisionEventObservable), _entityManager(&entityManager) {

}

void GravitySystem::update(double dt) {
    for(auto const &iterator: _entityManager->getAllEntitiesWithComponent<GravityComponent>()) {
        auto *moveComponent = _entityManager->getComponentFromEntity<MoveComponent>(iterator.first);
        if(!moveComponent) {
            _entityManager->addComponentToEntity<MoveComponent>(iterator.first, iterator.second->gravityApplied);
        } else {
            moveComponent->yVelocity += std::pow(iterator.second->gravityApplied, 2.5) * dt;
        }
    }
}

bool GravitySystem::canHandle(const CollisionEvent &collisionEvent) {
    return (collisionEvent.getCollisionAngle() >= 315 || collisionEvent.getCollisionAngle() <= 45) /*&& _entityManager->getComponentFromEntity<TurnComponent>(collisionEvent.getEntity()) != nullptr*/;
}

void GravitySystem::handleCollisionEvent(const CollisionEvent &collisionEvent) {
    auto *moveComponent = _entityManager->getComponentFromEntity<MoveComponent>(collisionEvent.getEntity());
    moveComponent->yVelocity = 0;
}
