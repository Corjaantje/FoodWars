#include "../../../Headers/GameECS/Events/CollisionEventHandlerLamda.h"

CollisionEventHandlerLamda::CollisionEventHandlerLamda(IObservable<CollisionEvent> &collisionEventObservable,
                                                       const std::function<bool(const CollisionEvent &collisionEvent)> &canHandleCollisionEventFunction,
                                                       const std::function<void(const CollisionEvent &collisionEvent)> &handleCollisionEventFunction) :
                                                               CollisionEventHandler(collisionEventObservable),
                                                               _canHandleCollisionEventFunction(canHandleCollisionEventFunction),
                                                               _handleCollisionEventFunction(handleCollisionEventFunction) {

}

bool CollisionEventHandlerLamda::canHandle(const CollisionEvent &collisionEvent) {
    return _canHandleCollisionEventFunction(collisionEvent);
}

void CollisionEventHandlerLamda::handleCollisionEvent(const CollisionEvent &collisionEvent) {
    _handleCollisionEventFunction(collisionEvent);
}
