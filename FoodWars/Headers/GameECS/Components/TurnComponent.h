//
// Created by pietb on 15-Oct-18.
//

#ifndef PROJECT_SWA_TURNCOMPONENT_H
#define PROJECT_SWA_TURNCOMPONENT_H

#include "Component.h"
#include "../../../../TonicEngine/Headers/Storage/ISerializable.h"

class TurnComponent: public Component, ISerializable {
public:
    TurnComponent();
    TurnComponent(int energy);
    TurnComponent(int energy, bool myTurn); // May be useless?
    ~TurnComponent() override;

    void switchTurn(bool change);
    void setRemainingTime(double t);
    void lowerRemainingTime(double t);
    double getRemainingTime() const;
    bool isMyTurn() const;
    void setEnergy(int energy);
    void setMaxEnergy(int energy);
    std::vector<std::string> serialize() override;

private:
    int _energy;
    int _maxEnergy;
    double _remainingTime;
    bool _myTurn = false;
};


#endif //PROJECT_SWA_TURNCOMPONENT_H
