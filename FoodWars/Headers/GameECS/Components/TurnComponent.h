//
// Created by pietb on 15-Oct-18.
//

#ifndef PROJECT_SWA_TURNCOMPONENT_H
#define PROJECT_SWA_TURNCOMPONENT_H

#include "Component.h"

class TurnComponent: public Component {
public:
    TurnComponent();
    TurnComponent(int energy);
    TurnComponent(int energy, bool myTurn); // May be useless?
    ~TurnComponent() override;

    void switchTurn(bool change);
    void setRemainingTime(double t);
    void lowerRemainingTime(double t);
    void resetEnergyToMax();
    double getRemainingTime() const;
    bool getMyTurn() const;
    int getmyEnergy() const;

private:
    int _maxEnergy;
    int _currentEnergy;
    double _remainingTime;
    bool _myTurn = false;
};


#endif //PROJECT_SWA_TURNCOMPONENT_H
