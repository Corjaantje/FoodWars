//
// Created by bryanvanlierop on 12/13/2018.
//

#ifndef PROJECT_SWA_TURNSWITCHEDEVENT_H
#define PROJECT_SWA_TURNSWITCHEDEVENT_H

class TurnSwitchedEvent {
private:
    int _playerTurn;
public:
    explicit TurnSwitchedEvent(int playerTurn);
    ~TurnSwitchedEvent();
    int getPlayerTurn() const;
};
#endif //PROJECT_SWA_TURNSWITCHEDEVENT_H
