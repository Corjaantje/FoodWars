#include "../../../Headers/GameECS/Systems/JumpSystem.h"
#include "../../../Headers/GameECS/Components/JumpComponent.h"
#include "../../../Headers/GameECS/Components/TurnComponent.h"
#include "../../../Headers/GameECS/Components/MoveComponent.h"
#include "../../../Headers/GameECS/Components/PlayerComponent.h"

void JumpSystem::update(double dt) {
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<JumpComponent>()) {
        if(!iterator.second) {
            _entityManager->removeComponentFromEntity<JumpComponent>(iterator.first);
            continue;
        }
        auto *moveComponent = _entityManager->getComponentFromEntity<MoveComponent>(iterator.first);
        if(!moveComponent) {
            _entityManager->addComponentToEntity<MoveComponent>(iterator.first);
            moveComponent = _entityManager->getComponentFromEntity<MoveComponent>(iterator.first);
        }
        double accelerationChange = iterator.second->getAcceleration() * dt * 15;
        moveComponent->yVelocity -= accelerationChange;
        iterator.second->setAcceleration(iterator.second->getAcceleration() - accelerationChange);
    }
}

JumpSystem::JumpSystem(EntityManager &entityManager,
                       const std::shared_ptr<InputFacade> &inputFacade,
                       const std::shared_ptr<AudioFacade>& audioFacade,
                       IObservable<CollisionEvent> &collisionEventObservable) :
        CollisionEventHandler(collisionEventObservable),
        _entityManager(&entityManager),
        _audioFacade{audioFacade} {
    inputFacade->getKeyEventObservable()->registerKeyEventObserver(this);
}

void JumpSystem::update(std::shared_ptr<KeyEvent> event) {
    if(event->getKeyEventType() == KeyEventType::Down && event->getKey() == KEY::KEY_SPACEBAR) {
        for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
            auto turnComponent = _entityManager->getComponentFromEntity<TurnComponent>(iterator.first);
            if(turnComponent->isMyTurn()){
                if(!_entityManager->getComponentFromEntity<JumpComponent>(iterator.first)) {
                    _entityManager->addComponentToEntity<JumpComponent>(iterator.first); // warning: this probably gives error!
                    turnComponent->lowerEnergy(5);
                //    _entityManager->addComponentToEntity(iterator.first, new JumpComponent);
                    _audioFacade->playEffect("jump");
                }
                break;
            }
        }
    }
}

bool JumpSystem::canHandle(const CollisionEvent &collisionEvent) {
    return (collisionEvent.getCollisionAngle() >= 315 || collisionEvent.getCollisionAngle() <= 45) && _entityManager->getComponentFromEntity<JumpComponent>(collisionEvent.getEntity()) != nullptr;
}

void JumpSystem::handleCollisionEvent(const CollisionEvent &collisionEvent) {
    _entityManager->removeComponentFromEntity<JumpComponent>(collisionEvent.getEntity());
}

