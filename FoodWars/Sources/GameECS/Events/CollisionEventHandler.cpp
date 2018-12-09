#include "../../../Headers/GameECS/Events/CollisionEventHandler.h"

void CollisionEventHandler::update(const CollisionEvent& collisionEvent) {
    if(canHandle(collisionEvent))
        handleCollisionEvent(collisionEvent);
}

CollisionEventHandler::CollisionEventHandler(IObservable<CollisionEvent> &collisionEventObservable) : _collisionEventObservable(&collisionEventObservable) {
    collisionEventObservable.registerObserver(this);
}

CollisionEventHandler::~CollisionEventHandler() {
    _collisionEventObservable->unregisterObserver(this);
}
