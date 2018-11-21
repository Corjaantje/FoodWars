#ifndef PROJECT_SWA_DAMAGEABLECOMPONENT_H
#define PROJECT_SWA_DAMAGEABLECOMPONENT_H

#include "Component.h"
#include "../../../../TonicEngine/Headers/Storage/ISerializable.h"

class DamageableComponent: public Component, ISerializable {

public:
    DamageableComponent();
    DamageableComponent(int health);
    ~DamageableComponent() override;
    const int GetHealth();
    void LowerHealth(int value);
    void IncreaseHealth(int value);
    void Destroy();
    const bool IsAlive();
    std::vector<std::string> serialize() override;
private:
    int _health; // 0 - 100
};
#endif //PROJECT_SWA_DAMAGEABLECOMPONENT_H
