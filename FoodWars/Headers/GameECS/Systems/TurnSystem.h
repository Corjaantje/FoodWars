//
// Created by pietb on 11-Oct-18.
//

#ifndef PROJECT_SWA_TURNSYSTEM_H
#define PROJECT_SWA_TURNSYSTEM_H

#include "IBaseSystem.h"
#include "../Components/TurnComponent.h"

//  Get components from the entity manager
//  Turn
//  Team
//  Controllable?

// Things important for the Turn System:
//  Array of Players
//      Players = Team Components
//  Array of Characters which a Player controls (probably included in a Player?)
//      Characters = Turn Components
//  Starting Player (starting character random?)
//  Turn max duration
//
//
//

//  RESPONSIBILITIES of the Turn System:
//  Keeping track of a turn's duration
//  Keeping the order of player's turns
//      What about the character's order? Keep track of this too, I presume.
//  Offer an indication that time's ticking
//      Additional warning in last 5 seconds
//
//
//
class TurnSystem : public IBaseSystem {


private:
    int _timePerTurn = 30;
//    double _remainingTime;

//    int _timePassed;
//    int timePassed();

    EntityManager* _entityManager;
//    std::vector<std::shared_ptr<TurnComponent>>* _turnComponents;
    // Change everything related to this monstrosity ^
    // So it just uses the crap from _entityManager
    //std::map<int, std::shared_ptr<Comp>>
    std::map<int, std::shared_ptr<TurnComponent>> _turnComponents;
    int _currentTurn = 0;
    std::vector<int> _turnOrder;

//    TurnComponent& _activeTurn;
    // delta time
    // 60 per sec, default
    // Passing of time is based on the delta time. 60 times per second by default and then time _timePerTurn
    // So for every 60 updates a second passes



public:
    // Treat 60 FPS as default
//    TurnSystem();
    TurnSystem(EntityManager* entityManager);
//    explicit TurnSystem(EntityManager* entityManager, int turnTime);
    ~TurnSystem() override;

//    void setRelevantEntities(std::vector<std::shared_ptr<TurnComponent>>* turns);//Turn[] ent);
    void getRelevantEntities();
    void setRelevantEntities(std::map<int, std::shared_ptr<TurnComponent>>* turns);
    void setTurnTime(int turnTime);

    void update(double deltaTime) override;
    void endTurn();

    // Uncertain if needed?
    // Would probably only be useful if we add a feature which allows you to switch to another character from your team.
    void switchCharacter(int charID);

    /*
        entities, get turn components
	        (2 entities terug, integer & component)

        Teams nog even negeren
        Steeds maar 1 heeft "myturn = true"
        Als beurt voorbij is, die op false en volgende true

        void/bool/something EndTurn() of EndTurn(Entity end)
     */
};


#endif //PROJECT_SWA_TURNSYSTEM_H
