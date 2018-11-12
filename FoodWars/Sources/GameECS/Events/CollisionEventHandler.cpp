#include "../../../Headers/GameECS/Events/CollisionEventHandler.h"

void CollisionEventHandler::update(std::shared_ptr<CollisionEvent> collisionEvent) {
    if(canHandle(*collisionEvent.get()))
        handleCollisionEvent(*collisionEvent.get());
}

CollisionEventHandler::CollisionEventHandler(IObservable<CollisionEvent> &collisionEventObservable) {
    collisionEventObservable.registerObserver(this);
}
