#ifndef PROJECT_SWA_ISHAPE_H
#define PROJECT_SWA_ISHAPE_H

#include "IRenderable.h"
#include "../IRenderer.h"

class Renderlist;
class IShape: public IRenderable {
public:
    int xPos;
    int yPos;
    int layer;
    IShape(int x, int y): xPos(x), yPos(y), layer(1) {

    }
    virtual ~IShape(){};
    virtual void addToRender(Renderlist* renderlist){};
};

#endif //PROJECT_SWA_ISHAPE_H
