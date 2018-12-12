#ifndef PROJECT_SWA_DAMAGEABLESYSTEM_H
#define PROJECT_SWA_DAMAGEABLESYSTEM_H

#include "IBaseSystem.h"
#include "../Components/DamageableComponent.h"
#include "../Events/CollisionEventHandler.h"
#include "../../../../TonicEngine/Headers/Audio/AudioFacade.h"
#include "../../DamageCalculator.h"

class DamageableSystem : public IBaseSystem, CollisionEventHandler {
private:
    EntityManager *_entityManager;
    AudioFacade* _audioFacade;
    DamageCalculator _damageCalculator;
public:
    DamageableSystem(EntityManager &entityManager, AudioFacade& audioFacade, IObservable<CollisionEvent> &collisionEventObservable);
    ~DamageableSystem() override;

    bool canHandle(const CollisionEvent& collisionEvent) override;
    void handleCollisionEvent(const CollisionEvent& collisionEvent) override;
    void handleInvertedCollisionEvent(const CollisionEvent& collisionEvent);
    void update(double deltaTime) override;

};

#endif //PROJECT_SWA_DAMAGEABLESYSTEM_H
