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
    AnimationManager* _animationManager;
public:
    explicit AnimationSystem(std::shared_ptr<EntityManager> entityManager, AnimationManager* animationManager);
    void update(double deltatime) override;
    std::shared_ptr<EntityManager>  _entityManager;
};


#endif //PROJECT_SWA_ANIMATIONSYSTEM_H
