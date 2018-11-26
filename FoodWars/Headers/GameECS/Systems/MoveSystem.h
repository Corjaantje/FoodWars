#ifndef PROJECT_SWA_MOVESYSTEM_H
#define PROJECT_SWA_MOVESYSTEM_H

#include "IBaseSystem.h"
#include "../../../../TonicEngine/Headers/Input/InputFacade.h"
#include "../Events/CollisionEvent.h"
#include "../Events/CollisionEventHandlerLamda.h"
#include "../../AnimationManager.h"

class MoveSystem : public IBaseSystem, public IObserver<KeyEvent> {
private:
    KEY _pressedKey;
    EntityManager *_entityManager;
    CollisionEventHandlerLamda* autoClimbOnCollision;
public:
    MoveSystem(EntityManager &entityManager, std::shared_ptr<InputFacade> inputFacade,
               IObservable<CollisionEvent> &collisionEventObservable);
    ~MoveSystem() override;
    void update(double dt) override;
    void update(std::shared_ptr<KeyEvent> event) override;
};

#endif //PROJECT_SWA_MOVESYSTEM_H
