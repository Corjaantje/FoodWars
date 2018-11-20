#ifndef PROJECT_SWA_RENDERLIST_H
#define PROJECT_SWA_RENDERLIST_H

#include <vector>
#include <map>
#include "Shapes/ShapeRectangle.h"
#include "Shapes/ShapeSprite.h"
#include "Shapes/ShapeText.h"

class Renderlist {
public:
    Renderlist() = default;
    ~Renderlist() = default;

    void clearLists();
public:
    std::map<int, std::vector<IShape*>> _shapes;
};


#endif //PROJECT_SWA_RENDERLIST_H
