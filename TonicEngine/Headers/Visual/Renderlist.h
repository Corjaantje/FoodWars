#ifndef PROJECT_SWA_RENDERLIST_H
#define PROJECT_SWA_RENDERLIST_H

#include <vector>
#include "Shapes/ShapeRectangle.h"
#include "Shapes/ShapeSprite.h"

class Renderlist {
public:
    Renderlist() = default;
    ~Renderlist() = default;
public:
    std::vector<ShapeRectangle> rectangleList;
    std::vector<ShapeSprite> spriteList;
};


#endif //PROJECT_SWA_RENDERLIST_H