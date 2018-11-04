#ifndef PROJECT_SWA_PLAYERCOMPONENT_H
#define PROJECT_SWA_PLAYERCOMPONENT_H

#include "Component.h"

class DamageableComponent: public Component {

public:
    DamageableComponent();
    DamageableComponent(int health);
    ~DamageableComponent() override;
    int GetHealth();
    void LowerHealth(int value);
    void IncreaseHealth(int value);
    bool IsAlive();
private:
    int health; // 0 - 100
};
#endif
