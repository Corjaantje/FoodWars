#ifndef PROJECT_SWA_ISHAPE_H
#define PROJECT_SWA_ISHAPE_H

#include "IRenderable.h"
#include "../IRenderer.h"


#include "../../Storage/ISerializable.h"

class Renderlist;
class IShape: public IRenderable, public ISerializable{
public:
    int xPos;
    int yPos;
    int layer;
    IShape(int x, int y): xPos(x), yPos(y), layer(1) {

    }
    IShape(int x, int y, int layer): xPos(x), yPos(y), layer(layer) {

    }

    ~IShape() override = default;
    virtual void addToRender(Renderlist* renderlist){};
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
};

#endif //PROJECT_SWA_ISHAPE_H
