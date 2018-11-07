#ifndef PROJECT_SWA_RENDERLIST_H
#define PROJECT_SWA_RENDERLIST_H

#include <vector>
#include "Shapes/ShapeRectangle.h"
#include "Shapes/ShapeSprite.h"
#include "Shapes/ShapeText.h"

class Renderlist {
public:
    Renderlist() = default;
    ~Renderlist() = default;

    void mergeShapeRectangles(std::vector<ShapeRectangle> _rectangleList);
    void mergeShapeSprites( std::vector<ShapeSprite> _spriteLis);
    void mergeShapeText(std::vector<ShapeText> _textList);
public:
    std::vector<ShapeRectangle> rectangleList;
    std::vector<ShapeSprite> spriteList;
    std::vector<ShapeText> textList;
};


#endif //PROJECT_SWA_RENDERLIST_H
