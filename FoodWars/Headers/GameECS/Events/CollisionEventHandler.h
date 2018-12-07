#ifndef PROJECT_SWA_COLLISIONEVENTHANDLER_H
#define PROJECT_SWA_COLLISIONEVENTHANDLER_H

#include "../../../../TonicEngine/Headers/Input/IObserver.h"
#include "CollisionEvent.h"
#include "../../../../TonicEngine/Headers/Input/IObservable.h"

class CollisionEventHandler : IObserver<CollisionEvent> {
private:
    IObservable<CollisionEvent>* _collisionEventObservable;
public:
    CollisionEventHandler(IObservable<CollisionEvent>& collisionEventObservable);
    ~CollisionEventHandler();
    virtual void handleCollisionEvent(const CollisionEvent& collisionEvent) = 0;
    virtual bool canHandle(const CollisionEvent& collisionEvent) = 0;
    void update(std::shared_ptr<CollisionEvent> collisionEvent) final;
};

#endif //PROJECT_SWA_COLLISIONEVENTHANDLER_H
