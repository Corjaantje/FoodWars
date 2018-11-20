#ifndef PROJECT_SWA_DAMAGEABLECOMPONENT_H
#define PROJECT_SWA_DAMAGEABLECOMPONENT_H

#include "Component.h"

class DamageableComponent: public Component {

public:
    DamageableComponent();
    DamageableComponent(int health);
    ~DamageableComponent() override;
    const int GetHealth();
    void LowerHealth(int value);
    void IncreaseHealth(int value);
    void Destroy();
    const bool IsAlive();
private:
    int _health; // 0 - 100
};
#endif //PROJECT_SWA_DAMAGEABLECOMPONENT_H
