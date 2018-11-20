#ifndef PROJECT_SWA_DAMAGINGCOMPONENT_H
#define PROJECT_SWA_DAMAGINGCOMPONENT_H

#include "Component.h"

class DamagingComponent : public Component {

public:
    DamagingComponent();
    DamagingComponent(int damage);
    ~DamagingComponent() override;
    const int GetDamage();
    void SetDamage(int damage);
private:
    int _damage;
};

#endif //PROJECT_SWA_DAMAGINGCOMPONENT_H
