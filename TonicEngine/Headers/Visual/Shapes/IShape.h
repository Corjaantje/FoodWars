#ifndef PROJECT_SWA_ISHAPE_H
#define PROJECT_SWA_ISHAPE_H

#include "IRenderable.h"
#include "../IRenderer.h"


#include "../../Storage/ISerializable.h"
#include "../../Storage/SerializationReceiver.h"

class Renderlist;

class IShape : public IRenderable, public SerializationReceiver {
public:
    int xPos;
    int yPos;
    int layer;

    IShape() : IShape(0, 0) {

    }

    IShape(int x, int y): xPos(x), yPos(y), layer(1) {

    }
    IShape(int x, int y, int layer): xPos(x), yPos(y), layer(layer) {

    }

    ~IShape() override = default;
    virtual void addToRender(Renderlist* renderlist){};
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;

    void accept(SerializationVisitor &visitor) override {
        visitor.visit("xPos", xPos);
        visitor.visit("yPos", yPos);
        visitor.visit("layer", layer);
    }
};

#endif //PROJECT_SWA_ISHAPE_H
