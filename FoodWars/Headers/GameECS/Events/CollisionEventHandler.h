#ifndef PROJECT_SWA_COLLISIONEVENTHANDLER_H
#define PROJECT_SWA_COLLISIONEVENTHANDLER_H

#include "../../../../TonicEngine/Headers/Input/IObserver.h"
#include "CollisionEvent.h"
#include "../../../../TonicEngine/Headers/Input/IObservable.h"

class CollisionEventHandler : IObserver<CollisionEvent> {
private:
public:
    CollisionEventHandler(IObservable<CollisionEvent>& collisionEventObservable);
    virtual void handleCollisionEvent(const CollisionEvent& collisionEvent) = 0;
    virtual bool canHandle(const CollisionEvent& collisionEvent) = 0;
    void update(std::shared_ptr<CollisionEvent> collisionEvent) final;
};

#endif //PROJECT_SWA_COLLISIONEVENTHANDLER_H
