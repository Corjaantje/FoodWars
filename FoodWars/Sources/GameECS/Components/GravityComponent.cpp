#include "../../../Headers/GameECS/Components/GravityComponent.h"

GravityComponent::GravityComponent() {
    gravityApplied = 15;
}

std::vector<std::string> GravityComponent::serialize() {
    std::vector<std::string> data;
    data.push_back(std::to_string(gravityApplied));

    return data;
}
