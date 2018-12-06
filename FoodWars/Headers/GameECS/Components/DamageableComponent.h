#ifndef PROJECT_SWA_DAMAGEABLECOMPONENT_H
#define PROJECT_SWA_DAMAGEABLECOMPONENT_H

#include "Component.h"
#include "../../../../TonicEngine/Headers/Storage/ISerializable.h"

class DamageableComponent: public Component, ISerializable {

public:
    DamageableComponent();
    explicit DamageableComponent(int health);
    DamageableComponent(int health, int resist);
    ~DamageableComponent() override;
    const int getHealth();
    const int getResistance();
    void lowerHealth(int value);
    void increaseHealth(int value);
    void setResistance(int value);
    void destroy();
    bool isAlive() const;
    std::vector<std::string> serialize() override;
private:
    int _health; // 0 - 100
    int _resistance;
};
#endif //PROJECT_SWA_DAMAGEABLECOMPONENT_H
