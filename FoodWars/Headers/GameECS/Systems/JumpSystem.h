#ifndef PROJECT_SWA_JUMPSYSTEM_H
#define PROJECT_SWA_JUMPSYSTEM_H

#include "IBaseSystem.h"
#include "../../../../TonicEngine/Headers/Input/InputFacade.h"
#include "../Events/CollisionEvent.h"
#include "../Events/CollisionEventHandler.h"
#include "../../../../TonicEngine/Headers/Audio/AudioFacade.h"

class JumpSystem : public IBaseSystem, public IObserver<KeyEvent>, public CollisionEventHandler  {
private:
    std::shared_ptr<EntityManager> _entityManager;
    std::shared_ptr<AudioFacade> _audioFacade;
    bool _jumpPressed;
public:
    JumpSystem(const std::shared_ptr<EntityManager>& entityManager, const std::shared_ptr<InputFacade>& inputFacade, const std::shared_ptr<AudioFacade>& audioFacade, IObservable<CollisionEvent>& collisionEventObservable);
    void update(double dt) override;
    void update(std::shared_ptr<KeyEvent> event) override;
    bool canHandle(const CollisionEvent& collisionEvent) override;
    void handleCollisionEvent(const CollisionEvent& collisionEvent) override;
};

#endif //PROJECT_SWA_JUMPSYSTEM_H
