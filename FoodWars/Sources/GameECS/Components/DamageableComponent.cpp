#include "../../../Headers/GameECS/Components/DamageableComponent.h"

DamageableComponent::DamageableComponent(int health) : _health{health} {}

DamageableComponent::DamageableComponent() : _health{100} {}

const bool DamageableComponent::IsAlive() {
    return _health > 0;
}

const int DamageableComponent::GetHealth() {
    return _health;
}

void DamageableComponent::LowerHealth(int value) {
    _health -= value;
}

void DamageableComponent::IncreaseHealth(int value) {
    _health += value;
}

void DamageableComponent::Destroy() {
    _health = 0;
}
DamageableComponent::~DamageableComponent() = default;