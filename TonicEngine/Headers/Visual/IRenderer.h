#ifndef PROJECT_SWA_RENDERER_H
#define PROJECT_SWA_RENDERER_H

class ShapeLine;
class ShapeRectangle;
class ShapeText;
class ShapeSprite;

class IRenderer {
public:
    virtual void renderRectangle(const ShapeRectangle &rectangle) = 0;
    virtual void renderText(const ShapeText &text) = 0;
    virtual void renderSprite(const ShapeSprite &sprite) = 0;
    virtual void renderLine (const ShapeLine &line) = 0;
};

#endif //PROJECT_SWA_RENDERER_H
