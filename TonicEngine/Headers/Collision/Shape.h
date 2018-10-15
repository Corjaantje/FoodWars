#pragma once

#include "Vector2D.h"

struct Shape {
    Vector2D position;

    Shape();
    Shape(float x, float y);
    virtual ~Shape();
};
