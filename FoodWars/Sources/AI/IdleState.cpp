#include <utility>

#include <iostream>
#include "../../Headers/AI/IdleState.h"
#include "../../Headers/GameECS/Components/AIComponent.h"
#include "../../Headers/AI/ScavengeState.h"
#include "../../Headers/AI/AttackState.h"
#include "../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../TonicEngine/Headers/Visual/Colour.h"
#include <math.h>
#include "../../../TonicEngine/Headers/Visual/Shapes/ShapeRectangle.h"

IdleState::IdleState(EntityManager &entityManager, int entityId, AISystem &context) : State(entityManager,
                                                                                            entityId,
                                                                                            context) {

}

void IdleState::enter() {
    std::cout << "Entering idle state" << std::endl;
}

void IdleState::execute(double dt) {
    //std::cout << "Executing idle state" << std::endl;
    // Stop walking
    _moveComponent->xVelocity = 0;

    // if my turn, calculate new state
    if(_turnComponent->isMyTurn()) {
        double centerX = _positionComponent->X + _boxCollider->width/2.0;
        double centerY = _positionComponent->Y + _boxCollider->height/2.0;
        for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
            auto * _targetPosition = _entityManager->getComponentFromEntity<PositionComponent>(iterator.first);
            double distanceToEnemy = abs(_positionComponent->X - _targetPosition->X) /*+ abs(_positionComponent->Y - _targetPosition->Y)*/;
            if(distanceToEnemy > 700) {
                PositionComponent target{0, _targetPosition->Y};
                int targetEntity = _entityManager->createEntity();
                if(_targetPosition->X < _positionComponent->X) target.X = _targetPosition->X + (700 - _boxCollider->width);
                if(_targetPosition->X > _positionComponent->X) target.X = _targetPosition->X - (700 - _boxCollider->width);
                _entityManager->addComponentToEntity<PositionComponent>(targetEntity, target.X, target.Y);
                _entityManager->addComponentToEntity<DrawableComponent>(targetEntity,
                        std::make_unique<ShapeRectangle>(10, 10, target.X, target.Y, Colour{0, 0, 0, 255}));
                // Scavenge state
                _aiComponent->setCurrentState(std::make_unique<ScavengeState>(*_entityManager, _entityId, target, *_context));
            } else {
                // Attack state
                _aiComponent->setCurrentState(std::make_unique<AttackState>(*_entityManager, _entityId, *_targetPosition, *_entityManager->getComponentFromEntity<DamageableComponent>(iterator.first), *_context));
            }
        }
    }
}

void IdleState::exit() {

}
