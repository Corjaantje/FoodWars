#include "../../../../Headers/GameECS/Components/Collider/BoxCollider.h"

BoxCollider::BoxCollider() {
    width = 0;
    height = 0;
}

BoxCollider::BoxCollider(int width, int height) : width(width), height(height) {

}

BoxCollider::~BoxCollider() {

}

