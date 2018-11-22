#ifndef PROJECT_SWA_COLLISENEVENTHANDLERLAMDA_H
#define PROJECT_SWA_COLLISENEVENTHANDLERLAMDA_H

#include "CollisionEventHandler.h"

class CollisionEventHandlerLamda : public CollisionEventHandler {
private:
    std::function<void(const CollisionEvent& collisionEvent)> _handleCollisionEventFunction;
    std::function<bool(const CollisionEvent& collisionEvent)> _canHandleCollisionEventFunction;
public:
    CollisionEventHandlerLamda(IObservable<CollisionEvent>& collisionEventObservable, const std::function<bool(const CollisionEvent& collisionEvent)>& canHandleCollisionEventFunction, const std::function<void(const CollisionEvent& collisionEvent)>& handleCollisionEventFunction);
    bool canHandle(const CollisionEvent& collisionEvent) final;
    void handleCollisionEvent(const CollisionEvent& collisionEvent) final;
};

#endif //PROJECT_SWA_COLLISENEVENTHANDLERLAMDA_H
