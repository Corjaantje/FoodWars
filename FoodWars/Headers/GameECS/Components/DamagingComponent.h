#ifndef PROJECT_SWA_DAMAGINGCOMPONENT_H
#define PROJECT_SWA_DAMAGINGCOMPONENT_H

#include "Component.h"
#include "../../StateMachine/Misc/FactionEnum.h"

class DamagingComponent : public Component {

public:
    DamagingComponent();
    explicit DamagingComponent(int damage);
    DamagingComponent(int damage, Faction faction);
    ~DamagingComponent() override;

    int getDamage() const;
    const Faction getFaction() const;

    void setDamage(int damage);

    void accept(SerializationVisitor &visitor) override;

    std::string getName() const override;

private:
    int _damage;
    Faction _faction;
};

#endif //PROJECT_SWA_DAMAGINGCOMPONENT_H
