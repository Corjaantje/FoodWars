#ifndef PROJECT_SWA_DRAWSYSTEM_H
#define PROJECT_SWA_DRAWSYSTEM_H


#include "IBaseSystem.h"

class DrawSystem : public IBaseSystem {
private:
    EntityManager* _entityManager;
public:
    DrawSystem(EntityManager* entityManager);
    ~DrawSystem();

    void update(double dt) override;
};


#endif //PROJECT_SWA_DRAWSYSTEM_H
