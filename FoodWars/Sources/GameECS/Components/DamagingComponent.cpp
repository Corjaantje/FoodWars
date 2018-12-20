#include "../../../Headers/GameECS/Components/DamagingComponent.h"

DamagingComponent::DamagingComponent() : _damage{20}, _faction{Faction::WHITE}{}

DamagingComponent::DamagingComponent(int damage) : _damage{damage}, _faction{Faction::WHITE} {}

DamagingComponent::DamagingComponent(int damage, Faction faction) : _damage{damage}, _faction{faction}{}

DamagingComponent::~DamagingComponent() = default;

int DamagingComponent::getDamage() const { return _damage; }
const Faction DamagingComponent::getFaction() const { return _faction; }

void DamagingComponent::setDamage(int damage) { _damage = damage; }

void DamagingComponent::accept(SerializationVisitor &visitor) {
    visitor.visit("damage", _damage);
}

std::string DamagingComponent::getName() const {
    return "DamagingComponent";
}
