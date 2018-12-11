#include "../../../Headers/GameECS/Components/DamagingComponent.h"

DamagingComponent::DamagingComponent() : _damage{20} {}

DamagingComponent::DamagingComponent(int damage) : _damage{damage} {}

DamagingComponent::~DamagingComponent() = default;

int DamagingComponent::getDamage() { return _damage; }

void DamagingComponent::setDamage(int damage) { _damage = damage; }

void DamagingComponent::accept(SerializationVisitor &visitor) {
    visitor.visit("damage", _damage);
}

std::string DamagingComponent::getName() const {
    return "DamagingComponent";
}
