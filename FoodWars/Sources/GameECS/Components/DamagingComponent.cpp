#include "../../../Headers/GameECS/Components/DamagingComponent.h"

DamagingComponent::DamagingComponent() : _damage{20} {}
DamagingComponent::DamagingComponent(int damage) : _damage{damage} {}
DamagingComponent::~DamagingComponent() = default;

const int DamagingComponent::GetDamage() { return _damage; }
void DamagingComponent::SetDamage(int damage) { _damage = damage; }