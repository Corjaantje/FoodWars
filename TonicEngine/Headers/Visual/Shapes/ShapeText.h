#ifndef PROJECT_SWA_SHAPETEXT_H
#define PROJECT_SWA_SHAPETEXT_H

#include <string>
#include "IShape.h"
#include "../Colour.h"

class ShapeText : public IShape {
public:
    ShapeText(int x, int y, std::string string, int fontSize, int width, int height, Colour colour);
    ~ShapeText() override;
    void addToRender(Renderlist* renderlist) override;
    void render(IRenderer &renderer) const override;
    std::string toString();
public:
    std::string text;
    int fontSize;
    int width;
    int height;
    Colour colour;
    int layer;
};


#endif //PROJECT_SWA_SHAPETEXT_H
