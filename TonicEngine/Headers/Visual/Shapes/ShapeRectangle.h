#ifndef PROJECT_SWA_SHAPERECTANGLE_H
#define PROJECT_SWA_SHAPERECTANGLE_H


#include "../Colour.h"
#include "IShape.h"

class ShapeRectangle : public IShape {
public:
    ShapeRectangle(int width, int height, int xPos, int yPos, Colour colour);
    ~ShapeRectangle() override;
    void addToRender(Renderlist* renderlist) override;
public:
    int width;
    int height;
    Colour colour;
};


#endif //PROJECT_SWA_SHAPERECTANGLE_H
