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
    std::map<int, std::shared_ptr<TurnComponent>> _turnComponents;
    int _currentTurn = 0;
    std::vector<int> _turnOrder;

public:
    TurnSystem(std::shared_ptr<EntityManager> entityManager);
    ~TurnSystem() override;

    void getRelevantEntities();
    void setRelevantEntities(std::map<int, std::shared_ptr<TurnComponent>>* turns);
    void setTurnTime(int turnTime);

    void update(double deltaTime) override;
    void endTurn();

    // Uncertain if needed?
    // Would probably only be useful if we add a feature which allows you to switch to another character from your team.
    void switchCharacter(int charID);
};


#endif //PROJECT_SWA_TURNSYSTEM_H
