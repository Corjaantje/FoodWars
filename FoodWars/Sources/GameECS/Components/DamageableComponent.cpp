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
    if ((_health - value) < 0)
        _health = 0;
    else _health -= value;
}

void DamageableComponent::IncreaseHealth(int value) {
    _health += value;
}

void DamageableComponent::Destroy() {
    _health = 0;
}

std::vector<std::string> DamageableComponent::serialize() {
    std::vector<std::string> data;
    data.emplace_back("damageablecomponent");
    data.emplace_back("health");
    data.emplace_back(std::to_string(_health));
    return data;
}

DamageableComponent::~DamageableComponent() = default;