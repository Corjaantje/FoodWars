#pragma once

#include "Shape.h"

struct Rectangle : Shape
{
    int width;
    int height;

    Rectangle();
    Rectangle(float x, float y, int width, int height);
    ~Rectangle();
};
