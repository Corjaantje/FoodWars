#include "../../../../Headers/GameECS/Components/Collider/BoxCollider.h"

BoxCollider::BoxCollider() : width{0}, height{0}, isVirtual{false} {
}

BoxCollider::BoxCollider(int width, int height) : width(width), height(height), isVirtual{false} {

}

BoxCollider::BoxCollider(int width, int height, bool isVirtual) : width(width), height(height), isVirtual{isVirtual} {

}

BoxCollider::~BoxCollider() = default;

void BoxCollider::accept(SerializationVisitor &visitor) {
    visitor.visit("width", width);
    visitor.visit("height", height);
    visitor.visit("isVirtual", isVirtual);
}

std::string BoxCollider::getName() const {
    return "BoxCollider";
}