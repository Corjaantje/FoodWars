#include "../../../Headers/GameECS/Components/DamageableComponent.h"

DamageableComponent::DamageableComponent(int health) : _health{health}, _resistance{0} {

}

DamageableComponent::DamageableComponent() : _health{100}, _resistance{0} {}

bool DamageableComponent::isAlive() {
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

void DamageableComponent::accept(SerializationVisitor &visitor) {
    visitor.visit("health", _health);
    visitor.visit("resistance", _resistance);
}

DamageableComponent::~DamageableComponent() = default;