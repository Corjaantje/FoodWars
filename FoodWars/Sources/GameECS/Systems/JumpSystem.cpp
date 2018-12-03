#include "../../../Headers/GameECS/Systems/JumpSystem.h"
#include "../../../Headers/GameECS/Components/JumpComponent.h"
#include "../../../Headers/GameECS/Components/TurnComponent.h"
#include "../../../Headers/GameECS/Components/MoveComponent.h"

JumpSystem::JumpSystem(EntityManager &entityManager, AudioFacade& audioFacade,
                        InputFacade& inputFacade,
                       IObservable<CollisionEvent>& collisionEventObservable) :
                       CollisionEventHandler(collisionEventObservable),
                       _entityManager(&entityManager),
                       _audioFacade{&audioFacade}
{
    inputFacade.getKeyEventObservable().registerKeyEventObserver(this);
}

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

void JumpSystem::update(const KeyEvent& event) {
    if(event.getKeyEventType() == KeyEventType::Down && event.getKey() == KEY::KEY_SPACEBAR) {
        for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<TurnComponent>()) {
            if(iterator.second->isMyTurn()){
                if(!_entityManager->getComponentFromEntity<JumpComponent>(iterator.first)) {
                    _entityManager->addComponentToEntity<JumpComponent>(
                            iterator.first); // warning: this probably gives error!
                    iterator.second->lowerEnergy(5);
                    _audioFacade->playEffect("jump");
                }
                break;
            }
        }
    }
}

bool JumpSystem::canHandle(const CollisionEvent &collisionEvent) {
    return (collisionEvent.getCollisionAngle() >= 270 || collisionEvent.getCollisionAngle() <= 90) && _entityManager->getComponentFromEntity<JumpComponent>(collisionEvent.getEntity()) != nullptr;
}

void JumpSystem::handleCollisionEvent(const CollisionEvent &collisionEvent) {
    _entityManager->removeComponentFromEntity<JumpComponent>(collisionEvent.getEntity());
}

