#ifndef PROJECT_SWA_ANIMATIONSYSTEM_H
#define PROJECT_SWA_ANIMATIONSYSTEM_H

#include "IBaseSystem.h"
#include "../../AnimationManager.h"
#include "../../../Headers/GameECS/Components/AnimationComponent.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../Headers/GameECS/Components/TurnComponent.h"
#include "../../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../../Headers/GameECS/Components/MoveComponent.h"

class AnimationSystem : public IBaseSystem {
private:
    AnimationManager _animationManager;
    EntityManager *_entityManager;
public:
    explicit AnimationSystem(EntityManager &entityManager);
    void update(double deltatime) override;
};


#endif //PROJECT_SWA_ANIMATIONSYSTEM_H
