#include "../../../Headers/GameECS/Components/DamageableComponent.h"

DamageableComponent::DamageableComponent(int health) : _health{health}, _resistance{0} {}

DamageableComponent::DamageableComponent() : _health{100}, _resistance{0} {}

DamageableComponent::DamageableComponent(int health, int resist) : _health{health}, _resistance{resist} {}

bool DamageableComponent::isAlive() const {
    return _health > 0;
}

const int DamageableComponent::getHealth() {
    return _health;
}

const int DamageableComponent::getResistance() {
    return _resistance;
}

void DamageableComponent::lowerHealth(int value) {
    if ((_health - value) < 0)
        _health = 0;
    else _health -= value;
}

void DamageableComponent::increaseHealth(int value) {
    _health += value;
}

void DamageableComponent::setResistance(int value) {
    _resistance = value;
}

void DamageableComponent::destroy() {
    _health = 0;
}

std::vector<std::string> DamageableComponent::serialize() {
    std::vector<std::string> data;
    data.emplace_back("damageablecomponent");
    data.emplace_back("health");
    data.emplace_back(std::to_string(_health));
    data.emplace_back("resistance");
    data.emplace_back(std::to_string(_resistance));
    return data;
}

DamageableComponent::~DamageableComponent() = default;