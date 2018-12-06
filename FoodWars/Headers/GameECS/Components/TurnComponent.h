//
// Created by pietb on 15-Oct-18.
//

#ifndef PROJECT_SWA_TURNCOMPONENT_H
#define PROJECT_SWA_TURNCOMPONENT_H

#include "Component.h"
#include "../../../../TonicEngine/Headers/Storage/ISerializable.h"

class TurnComponent : public Component {
public:
    TurnComponent();

    explicit TurnComponent(double energy);
    TurnComponent(double energy, bool myTurn); // May be useless?
    ~TurnComponent() override;

    void switchTurn(bool change);
    void setRemainingTime(double t);
    void lowerEnergy(double delta);
    void lowerRemainingTime(double t);
    double getEnergy() const;
    void setEnergy(double energy);
    double getRemainingTime() const;
    bool isMyTurn() const;
    void setEnergy(int energy);

    void accept(SerializationVisitor &visitor) override;
private:
    double _energy;
    double _remainingTime;
    bool _myTurn = false;
};


#endif //PROJECT_SWA_TURNCOMPONENT_H
