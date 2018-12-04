#include <cmath>
#include "../../../Headers/GameECS/Systems/AISystem.h"
#include "../../../Headers/AI/ScavengeState.h"
#include "../../../Headers/AI/IdleState.h"

AISystem::AISystem(EntityManager &entityManager, const std::shared_ptr<AudioFacade>& audioFacade, IObservable<CollisionEvent>& collisionEventObservable)
                    : _entityManager(&entityManager), CollisionEventHandler(collisionEventObservable){
    _audioFacade = audioFacade;
}

AISystem::~AISystem() = default;


void AISystem::update(double dt) {

    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<AIComponent>()) {
        auto turnComponent = _entityManager->getComponentFromEntity<TurnComponent>(iterator.first);
        auto moveComponent = _entityManager->getComponentFromEntity<MoveComponent>(iterator.first);

        if (!turnComponent->isMyTurn()) {
            iterator.second->setCurrentState(std::make_unique<IdleState>());
            iterator.second->update(dt);
            continue;
        }
        else {
            // TODO: Choose a state

            // Scavenge
            iterator.second->setCurrentState(std::make_unique<ScavengeState>());
            iterator.second->update(dt);

            // Attack

            // Flee
        }
            //jump(iterator.first, *turnComponent);
            //walkRight(*moveComponent, *turnComponent, dt);
            //walkLeft(*moveComponent, *turnComponent, dt);






            /*if(moveComponent->xVelocity >= 0)
            {
                walkRight(*moveComponent, *turnComponent, dt);
            }
            std::cout << "Distance to enemy: " << getDistanceToEnemy(iterator.first) << std::endl;
            if(getDistanceToEnemy(iterator.first) < 800)
            {
                // TODO: Shoot towards enemy


            }
            auto positionComponent = _entityManager->getComponentFromEntity<PositionComponent>(iterator.first);
            if(positionComponent) {
                positionComponent->X += std::round(dt * moveComponent->xVelocity);
                positionComponent->Y += std::round(dt * moveComponent->yVelocity);
            }
        } else {
            moveComponent->xVelocity = 0;
        }*/
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

    countObstructingBlocks(positionComponentOne, positionComponentTwo);
    return 0; //abs((positionComponentOne->X + boxColliderOne->width) - (positionComponentTwo->X + boxColliderTwo->width)) + abs((positionComponentOne->Y + boxColliderOne->height) - (positionComponentTwo->Y + boxColliderTwo->height));
}

// List of entities between two points
int AISystem::countObstructingBlocks(PositionComponent* posOne, PositionComponent* posTwo){
    std::vector<int> obstructingBlocks;
    for(const auto& iterator: _entityManager->getAllEntitiesWithComponent<BoxCollider>())
    {
        auto positionComponent = _entityManager->getComponentFromEntity<PositionComponent>(iterator.first);
        // get all items between two points
        if((positionComponent->X >= posOne->X && positionComponent->X <= posTwo->X && positionComponent->Y >= posOne->Y && positionComponent->Y <= posTwo->Y) // two is bottom right of one
        || (positionComponent->X >= posOne->X && positionComponent->X <= posTwo->X && positionComponent->Y <= posOne->Y && positionComponent->Y >= posTwo->Y) // two is top right of one
        || (positionComponent->X <= posOne->X && positionComponent->X >= posTwo->X && positionComponent->Y >= posOne->Y && positionComponent->Y <= posTwo->Y) // two is bottom left of one
        || (positionComponent->X <= posOne->X && positionComponent->X >= posTwo->X && positionComponent->Y <= posOne->Y && positionComponent->Y >= posTwo->Y)) // two is top left of one
        {
            obstructingBlocks.push_back(iterator.first);
        }
    }
    // print entity Id's
    /*for(int i : obstructingBlocks){
        std::cout << "entityId: " << i << std::endl;
    }*/

    return 0;
}

bool AISystem::canHandle(const CollisionEvent &collisionEvent) {
    // met AIcomponent?
    // zonder damagingcomponent

    return false;
}

void AISystem::handleCollisionEvent(const CollisionEvent &collisionEvent) {
    // what to do now
}