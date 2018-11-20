#include "../../../Headers/GameECS/Components/GravityComponent.h"

GravityComponent::GravityComponent() : gravityApplied {15} {
}

GravityComponent::GravityComponent(double gravity) : gravityApplied {gravity}{
}
std::vector<std::string> GravityComponent::serialize() {
    std::vector<std::string> data;
    data.push_back(std::to_string(gravityApplied));

    return data;
}
