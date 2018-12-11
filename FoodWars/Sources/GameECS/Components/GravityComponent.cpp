#include "../../../Headers/GameECS/Components/GravityComponent.h"

GravityComponent::GravityComponent() : gravityApplied {15} {
}

GravityComponent::GravityComponent(double gravity) : gravityApplied {gravity}{

}

void GravityComponent::accept(SerializationVisitor &visitor) {
    visitor.visit("gravityApplied", gravityApplied);
}

std::string GravityComponent::getName() const {
    return "GravityComponent";
}
