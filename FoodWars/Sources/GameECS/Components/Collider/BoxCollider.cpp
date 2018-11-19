#include "../../../../Headers/GameECS/Components/Collider/BoxCollider.h"

BoxCollider::BoxCollider() {
    width = 0;
    height = 0;
}

BoxCollider::BoxCollider(int width, int height) : width(width), height(height) {

}

BoxCollider::~BoxCollider() {

}

std::vector<std::string> BoxCollider::serialize() {
    std::vector<std::string> data;
    data.emplace_back("collidecomponent");
    data.emplace_back("width");
    data.emplace_back(std::to_string(width));
    data.emplace_back("height");
    data.emplace_back(std::to_string(height));
    return data;
}

