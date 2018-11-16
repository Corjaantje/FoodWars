//
// Created by pietb on 11-Oct-18.
//

#ifndef PROJECT_SWA_TURNSYSTEM_H
#define PROJECT_SWA_TURNSYSTEM_H

#include "IBaseSystem.h"
#include "../Components/TurnComponent.h"

class TurnSystem : public IBaseSystem {


private:
    int _timePerTurn;
    int _defaultTimePerTurn = 30;
    std::shared_ptr<EntityManager> _entityManager;
public:
    TurnSystem(std::shared_ptr<EntityManager> entityManager);
    ~TurnSystem() override;
    void update(double deltaTime) override;
};


#endif //PROJECT_SWA_TURNSYSTEM_H
