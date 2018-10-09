#include "../../Headers/Collision/Circle.h"

Circle::Circle() {
    this->radius = 0.0;
}
Circle::Circle(float x, float y, float radius) : Shape(x, y) {
    this->radius = radius;
}
Circle::~Circle() {}

