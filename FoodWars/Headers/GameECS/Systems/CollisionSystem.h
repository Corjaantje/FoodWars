#ifndef PROJECT_SWA_COLLISIONSYSTEM_H
#define PROJECT_SWA_COLLISIONSYSTEM_H

#include "IBaseSystem.h"
#include "../Events/CollisionEvent.h"
#include "../../../../TonicEngine/Headers/Input/IObservable.h"

class CollisionSystem : public IBaseSystem, public IObservable<CollisionEvent> {
private:
    std::shared_ptr<EntityManager> _entityManager;
public:
    CollisionSystem(std::shared_ptr<EntityManager> entityManager);
    void update(double dt) override;

};

#endif //PROJECT_SWA_COLLISIONSYSTEM_H
