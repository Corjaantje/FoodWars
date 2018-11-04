#include "../../../Headers/GameECS/Components/DamageableComponent.h"

DamageableComponent::DamageableComponent(int health) {
    this->health = health;
}

DamageableComponent::DamageableComponent() {
    health = 100;
}

bool DamageableComponent::IsAlive() {
    return health <= 0;
}

int DamageableComponent::GetHealth() {
    return health;
}

void DamageableComponent::LowerHealth(int value) {
    health -= value;
}

void DamageableComponent::IncreaseHealth(int value) {
    health += value;
}

DamageableComponent::~DamageableComponent() = default;