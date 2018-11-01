

#ifndef PROJECT_SWA_MOVESYSTEM_H
#define PROJECT_SWA_MOVESYSTEM_H

#include "IBaseSystem.h"
#include "../../../../TonicEngine/Headers/Input/InputFacade.h"
#include "../Events/CollisionEvent.h"
#include "../Events/CollisionEventHandlerLamda.h"

class MoveSystem : public IBaseSystem, public IObserver<KeyEvent> {
private:
    KEY _pressedKey;
    std::map<KEY, bool> _pressedKeys;
    std::shared_ptr<EntityManager> _entityManager;
    std::shared_ptr<KeyEventObservable> _keyEventObservable;
    CollisionEventHandlerLamda* trapWalkOnCollision;
public:
    MoveSystem(std::shared_ptr<EntityManager> entityManager, std::shared_ptr<InputFacade> inputFacade, IObservable<CollisionEvent>& collisionEventObservable);
    ~MoveSystem() override;
    void update(double dt) override;
    void update(std::shared_ptr<KeyEvent> event) override;
    //void update(std::shared_ptr<std::map<KEY, bool>> event) override;
};

#endif //PROJECT_SWA_MOVESYSTEM_H
