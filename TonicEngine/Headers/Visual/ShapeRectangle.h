#ifndef PROJECT_SWA_SHAPERECTANGLE_H
#define PROJECT_SWA_SHAPERECTANGLE_H


#include "Colour.h"

class ShapeRectangle {
public:
    ShapeRectangle(int width, int height, int xPos, int yPos, Colour colour);
    ~ShapeRectangle();
public:
    int width;
    int height;
    int xPos;
    int yPos;
    Colour colour;
};


#endif //PROJECT_SWA_SHAPERECTANGLE_H
