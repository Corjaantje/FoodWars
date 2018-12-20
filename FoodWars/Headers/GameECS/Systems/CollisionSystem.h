#ifndef PROJECT_SWA_COLLISIONSYSTEM_H
#define PROJECT_SWA_COLLISIONSYSTEM_H

#include "IBaseSystem.h"
#include "../Events/CollisionEvent.h"
#include "../../../../TonicEngine/Headers/Input/IObservable.h"

class CollisionSystem : public IBaseSystem, public IObservable<CollisionEvent> {
private:
    EntityManager *_entityManager;
public:
    explicit CollisionSystem(EntityManager &entityManager);
    void update(double dt) override;
};

#endif //PROJECT_SWA_COLLISIONSYSTEM_H
