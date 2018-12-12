#ifndef PROJECT_SWA_DAMAGECALCULATOR_H
#define PROJECT_SWA_DAMAGECALCULATOR_H

#include "../Headers/GameECS/Components/DamagingComponent.h"
#include "../Headers/GameECS/Components/DamageableComponent.h"
#include "StateMachine/Misc/FactionEnum.h"
#include "GameECS/Components/PlayerComponent.h"
#include "GameECS/Systems/Misc/FactionComparer.h"

class DamageCalculator {
public:
    DamageCalculator();
    ~DamageCalculator();
    int calculateDamage(DamagingComponent& projectile, DamageableComponent& target, PlayerComponent& playerTarget);
private:
    FactionComparer _factionComparer;
    int applyResistance(int currentDamage, int targetResistance);
    int applyFactionDamage(int currentDamage, Faction projectileFaction, Faction targetFaction);
};
#endif //PROJECT_SWA_DAMAGECALCULATOR_H
