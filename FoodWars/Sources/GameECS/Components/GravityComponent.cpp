#include "../../../Headers/GameECS/Components/GravityComponent.h"

GravityComponent::GravityComponent() : gravityApplied {15} {
}

GravityComponent::GravityComponent(double gravity) : gravityApplied {gravity}{
}