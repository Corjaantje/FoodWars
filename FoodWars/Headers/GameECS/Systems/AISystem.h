#ifndef PROJECT_SWA_AISYSTEM_H
#define PROJECT_SWA_AISYSTEM_H

#include "IBaseSystem.h"
#include "../Events/CollisionEvent.h"
#include "../../../../TonicEngine/Headers/Input/IObservable.h"
#include "../../../../TonicEngine/Headers/Input/InputFacade.h"
#include "../Events/CollisionEventHandlerLamda.h"

class AISystem : public IBaseSystem{
private:
    std::shared_ptr<EntityManager> _entityManager;
    CollisionEventHandlerLamda* autoClimbOnCollision;
public:
    AISystem(std::shared_ptr<EntityManager> entityManager, IObservable<CollisionEvent>& collisionEventObservable);
    ~AISystem() override;
    void update(double dt) override;
};


#endif //PROJECT_SWA_AISYSTEM_H
