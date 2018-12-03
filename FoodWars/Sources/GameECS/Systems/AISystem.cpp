#include <cmath>
#include "../../../Headers/GameECS/Systems/AISystem.h"

AISystem::AISystem(EntityManager &entityManager, const std::shared_ptr<AudioFacade>& audioFacade, IObservable<CollisionEvent>& collisionEventObservable) : _entityManager(&entityManager){
    _audioFacade = audioFacade;
}

AISystem::~AISystem() = default;


void AISystem::update(double dt) {

    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<AIComponent>()) {
        auto turnComponent = _entityManager->getComponentFromEntity<TurnComponent>(iterator.first);
        auto moveComponent = _entityManager->getComponentFromEntity<MoveComponent>(iterator.first);

        if (turnComponent->isMyTurn()) {
            //jump(iterator.first, *turnComponent);
            //walkRight(*moveComponent, *turnComponent, dt);
            walkLeft(*moveComponent, *turnComponent, dt);
            std::cout << "Distance to enemy: " << getDistanceToEnemy(iterator.first) << std::endl;
            auto positionComponent = _entityManager->getComponentFromEntity<PositionComponent>(iterator.first);
            if(positionComponent) {
                positionComponent->X += std::round(dt * moveComponent->xVelocity);
                positionComponent->Y += std::round(dt * moveComponent->yVelocity);
            }
        } else {
            moveComponent->xVelocity = 0;
        }
    }
}

void AISystem::jump(int entityId, TurnComponent& turnComponent){
    if(!_entityManager->getComponentFromEntity<JumpComponent>(entityId)) {
        _entityManager->addComponentToEntity<JumpComponent>(entityId);
        turnComponent.lowerEnergy(5);
        _audioFacade->playEffect("jump");
    }
}

void AISystem::walkLeft(MoveComponent& moveComponent, TurnComponent& turnComponent, double dt) {
    moveComponent.xVelocity = -100;
    turnComponent.lowerEnergy(walkingEnergyCostPerSecond * dt);
}

void AISystem::walkRight(MoveComponent& moveComponent, TurnComponent& turnComponent, double dt) {
    moveComponent.xVelocity = 100;
    turnComponent.lowerEnergy(walkingEnergyCostPerSecond * dt);
}

void AISystem::getAllCollidableEntities(){
    delete _collidableEntities;
    //_collidableEntities = nullptr;
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<BoxCollider>()){
        _collidableEntities->push_back(iterator.first);
    }

}

int AISystem::getDistanceToEnemy(int entityId) {
    for(const auto &iterator : _entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
        return calculateDistance(entityId, iterator.first);
    }
    // Player not found
    return 0;
}

// Calculates the manhattan distance between the centers two entities
int AISystem::calculateDistance(int entityOne, int entityTwo) {
    auto positionComponentOne = _entityManager->getComponentFromEntity<PositionComponent>(entityOne);
    auto positionComponentTwo = _entityManager->getComponentFromEntity<PositionComponent>(entityTwo);

    auto boxColliderOne = _entityManager->getComponentFromEntity<BoxCollider>(entityOne);
    auto boxColliderTwo = _entityManager->getComponentFromEntity<BoxCollider>(entityTwo);

    return abs((positionComponentOne->X + boxColliderOne->width) - (positionComponentTwo->X + boxColliderTwo->width)) + abs((positionComponentOne->Y + boxColliderOne->height) - (positionComponentTwo->Y + boxColliderTwo->height));
}

// Counts the amount of blocks positioned between two points
int AISystem::countObstructingBlocks(PositionComponent* posOne, PositionComponent* posTwo){
    // TODO: Only check blocks within a certain area

    // Refresh list of collidableEntities
    getAllCollidableEntities();

    return 0;
}

