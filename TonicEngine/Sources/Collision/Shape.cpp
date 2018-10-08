#include "../../Headers/Collision/Shape.h"

Shape::Shape() {
    position.Zero();
}
Shape::Shape(float x, float y) {
    position.x = x;
    position.y = y;
}
Shape::~Shape() {}