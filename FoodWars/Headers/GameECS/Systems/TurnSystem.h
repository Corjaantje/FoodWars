//
// Created by pietb on 11-Oct-18.
//

#ifndef PROJECT_SWA_TURNSYSTEM_H
#define PROJECT_SWA_TURNSYSTEM_H

#include "IBaseSystem.h"
#include "../Components/TurnComponent.h"

class TurnSystem : public IBaseSystem {
private:
    int _defaultTimePerTurn;
    int _timePerTurn;
    EntityManager *_entityManager;
public:
    TurnSystem(EntityManager &entityManager);
    ~TurnSystem() override;
    void switchTurn();
    void resetCurrentTime();
    void resetCurrentEnergy();
    int getCurrentPlayerID() const;
    double getCurrentPlayerEnergy() const;
    void update(double deltaTime) override;
};


#endif //PROJECT_SWA_TURNSYSTEM_H
