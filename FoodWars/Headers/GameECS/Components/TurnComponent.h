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
    ~TurnComponent() override;

    void switchTurn(bool change);
    void setRemainingTime(double t);
    void lowerEnergy(double delta);
    void lowerRemainingTime(double t);
    double getEnergy() const;
    void setEnergy(double energy);
    double getRemainingTime() const;
    bool isMyTurn() const;
    bool getIsShooting() const;
    void setIsShooting(bool change);
    void changeIsShooting();
    void setEnergy(int energy);

    void accept(SerializationVisitor &visitor) override;

    std::string getName() const override;

private:
    double _energy;
    double _remainingTime;
    bool _myTurn = false;
    bool _isShooting = false;
};


#endif //PROJECT_SWA_TURNCOMPONENT_H
