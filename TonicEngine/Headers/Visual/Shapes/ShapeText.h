#ifndef PROJECT_SWA_SHAPETEXT_H
#define PROJECT_SWA_SHAPETEXT_H

#include <string>
#include "IShape.h"
#include "../Colour.h"

class ShapeText : public IShape {
public:
    ShapeText(int x, int y, const std::string &string, int fontSize, int width, int height, Colour colour);
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

    int getWidth() const override { return width; }

    int getHeight() const override { return height; }

    void accept(SerializationVisitor &visitor) override;

    std::string getName() const override;
};


#endif //PROJECT_SWA_SHAPETEXT_H
