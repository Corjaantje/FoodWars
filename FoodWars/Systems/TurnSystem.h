//
// Created by pietb on 11-Oct-18.
//

#ifndef PROJECT_SWA_TURNSYSTEM_H
#define PROJECT_SWA_TURNSYSTEM_H

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
class TurnSystem {
    // Treat 60 FPS as default
    TurnSystem();
    explicit TurnSystem(int turnTime);
    ~TurnSystem();

private:
    int _timePerTurn = 30;


    int _timePassed;

    int timePassed();

    // delta time
    // 60 per sec, default
    // Passing of time is based on the delta time. 60 times per second by default and then time _timePerTurn
    // So for every 60 updates a second passes

public:
    void onUpdate();
    void endTurn();
    void onTurnEnd();

    // Uncertain if needed
    void switchCharacter(int charID);

};


#endif //PROJECT_SWA_TURNSYSTEM_H
