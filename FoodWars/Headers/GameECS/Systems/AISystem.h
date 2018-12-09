#ifndef PROJECT_SWA_AISYSTEM_H
#define PROJECT_SWA_AISYSTEM_H

#include "IBaseSystem.h"
#include "../Events/CollisionEvent.h"
#include "../../../../TonicEngine/Headers/Input/IObservable.h"
#include "../../../../TonicEngine/Headers/Input/InputFacade.h"
#include "../Events/CollisionEventHandlerLamda.h"
#include "../../../../TonicEngine/Headers/Audio/AudioFacade.h"
#include "../Components/TurnComponent.h"
#include "../Components/AIComponent.h"
#include "../../../Headers/GameECS/Components/MoveComponent.h"
#include "../../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../../Headers/GameECS/Components/TurnComponent.h"
#include "../../../Headers/GameECS/Components/JumpComponent.h"
#include "../../../../TonicEngine/Headers/Audio/AudioFacade.h"

class AISystem : public IBaseSystem{
private:
    EntityManager* _entityManager;
    AudioFacade* _audioFacade;
    IObservable<CollisionEvent>& _collisionEventObservable;

    void jump(int entityId, TurnComponent& turnComponent);
    void walkLeft(MoveComponent& moveComponent, TurnComponent& turnComponent, double dt);
    void walkRight(MoveComponent& moveComponent, TurnComponent& turnComponent, double dt);

public:
    AISystem(EntityManager &entityManager, AudioFacade& audioFacade, IObservable<CollisionEvent>& collisionEventObservable);
    ~AISystem() override;
    void update(double dt) override;
    IObservable<CollisionEvent>& getCollisionEventObservable();
    void generateProjectile(const PositionComponent &playerPositionComponent, const BoxCollider &playerCollider, double velocityX, double velocityY);
    //int getDistanceToEnemy(int entityId);
    //int calculateDistance(int entityOne, int entityTwo);
    //int countObstructingBlocks(PositionComponent* posOne, PositionComponent* posTwo);
};


#endif //PROJECT_SWA_AISYSTEM_H