#ifndef PROJECT_SWA_TURNSYSTEM_H
#define PROJECT_SWA_TURNSYSTEM_H

#include "IBaseSystem.h"
#include "../Components/TurnComponent.h"
#include "../../PowerupManager.h"

class TurnSystem : public IBaseSystem {
private:
    int _defaultTimePerTurn;
    int _timePerTurn;
    EntityManager *_entityManager;
    PowerupManager _powerupManager;
public:
    TurnSystem(EntityManager &entityManager);
    ~TurnSystem() override;
    void update(double deltaTime) override;
};


#endif //PROJECT_SWA_TURNSYSTEM_H
