#ifndef PROJECT_SWA_DAMAGINGCOMPONENT_H
#define PROJECT_SWA_DAMAGINGCOMPONENT_H

#include "Component.h"

class DamagingComponent : public Component {

public:
    DamagingComponent();

    explicit DamagingComponent(int damage);
    ~DamagingComponent() override;

    int getDamage();

    void setDamage(int damage);
private:
    int _damage;
};

#endif //PROJECT_SWA_DAMAGINGCOMPONENT_H
