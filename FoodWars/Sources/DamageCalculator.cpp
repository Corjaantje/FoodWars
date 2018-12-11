

#include "../Headers/DamageCalculator.h"
#include "../Headers/GameECS/Systems/Misc/FactionComparer.h"
#include <cmath>
#include <utility>

DamageCalculator::DamageCalculator() : _factionComparer{FactionComparer{}} {}
DamageCalculator::~DamageCalculator() = default;

int DamageCalculator::calculateDamage(DamagingComponent& projectile, DamageableComponent& target, PlayerComponent& playerTarget) {
    int damage = projectile.getDamage();

    /*
     * Faction::RED = Meat
     * Faction::GREEN = Vegan
     * Faction::YELLOW = Sweets
     * Faction::WHITE = Normal / None
     */
    damage = applyFactionDamage(damage, projectile.getFaction(), playerTarget.getFaction());
    damage = applyResistance(damage, target.getResistance());
    return damage;
}

int DamageCalculator::applyResistance(int currentDamage, int targetResistance) {
    return (int) std::round(currentDamage - (currentDamage * (targetResistance / 100.0)));
}

int DamageCalculator::applyFactionDamage(int currentDamage, Faction projectileFaction, Faction targetFaction) {
    auto strength = _factionComparer.getStrength(projectileFaction);
    if (strength == nullptr) return currentDamage;
    if (targetFaction == *strength) return (int) std::round(currentDamage * 1.15);
    return currentDamage;
}


