#ifndef PROJECT_SWA_SHAPERECTANGLE_H
#define PROJECT_SWA_SHAPERECTANGLE_H


#include "../Colour.h"
#include "IShape.h"

class ShapeRectangle : public IShape {
public:
    ShapeRectangle(int width, int height, int xPos, int yPos, Colour colour, int layer);
    ~ShapeRectangle() override;
    void addToRender(Renderlist* renderlist) override;
public:
    int width;
    int height;
    Colour colour;
    int layer;
    void render(IRenderer &renderer) const override;
};


#endif //PROJECT_SWA_SHAPERECTANGLE_H
