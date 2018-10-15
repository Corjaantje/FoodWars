#pragma once

#include "Shape.h"

struct Circle : Shape
{
public:
    float radius;

    Circle();
    Circle(float x, float y, float radius);
    ~Circle();
};
