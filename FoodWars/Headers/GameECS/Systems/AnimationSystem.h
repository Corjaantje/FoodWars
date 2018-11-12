#ifndef PROJECT_SWA_ANIMATIONSYSTEM_H
#define PROJECT_SWA_ANIMATIONSYSTEM_H


#include "IBaseSystem.h"

class AnimationSystem : public IBaseSystem {
public:
    explicit AnimationSystem(std::shared_ptr<EntityManager> entityManager);
    void update(double deltatime) override;
    std::shared_ptr<EntityManager>  _entityManager;
};


#endif //PROJECT_SWA_ANIMATIONSYSTEM_H
