#ifndef PROJECT_SWA_JUMPSYSTEM_H
#define PROJECT_SWA_JUMPSYSTEM_H

#include "IBaseSystem.h"
#include "../../../../TonicEngine/Headers/Input/InputFacade.h"
#include "../Events/CollisionEvent.h"
#include "../Events/CollisionEventHandler.h"
#include "../../../../TonicEngine/Headers/Audio/AudioFacade.h"

class JumpSystem : public IBaseSystem, public IObserver<KeyEvent>, public CollisionEventHandler  {
private:
    AudioFacade* _audioFacade;
    EntityManager *_entityManager;
public:
    JumpSystem(EntityManager &entityManager, AudioFacade& audioFacade, InputFacade& inputFacade, IObservable<CollisionEvent>& collisionEventObservable);
    void update(double dt) override;
    void update(const KeyEvent& event) override;
    bool canHandle(const CollisionEvent& collisionEvent) override;
    void handleCollisionEvent(const CollisionEvent& collisionEvent) override;
};

#endif //PROJECT_SWA_JUMPSYSTEM_H
