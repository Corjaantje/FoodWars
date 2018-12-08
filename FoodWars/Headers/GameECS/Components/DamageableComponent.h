#ifndef PROJECT_SWA_DAMAGEABLECOMPONENT_H
#define PROJECT_SWA_DAMAGEABLECOMPONENT_H

#include "Component.h"
#include "../../../../TonicEngine/Headers/Storage/ISerializable.h"

class DamageableComponent: public Component, ISerializable {

public:
    DamageableComponent();
    explicit DamageableComponent(int health);
    ~DamageableComponent() override;
    int GetHealth() const;
    void LowerHealth(int value);
    void IncreaseHealth(int value);
    void Destroy();
    bool IsAlive() const;
    std::vector<std::string> serialize() override;
private:
    int _health; // 0 - 100
};
#endif //PROJECT_SWA_DAMAGEABLECOMPONENT_H
