#include "../../Headers/Collision/Rectangle.h"

Rectangle::Rectangle() {
    this->width = 0;
    this->height = 0;
}
Rectangle::Rectangle(float x, float y, int width, int height) : Shape(x, y) {
    this->width = width;
    this->height = height;
}
Rectangle::~Rectangle() {}