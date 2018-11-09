#ifndef PROJECT_SWA_DRAWABLECOMPONENT_H
#define PROJECT_SWA_DRAWABLECOMPONENT_H


#include <bits/unique_ptr.h>
#include "Component.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/IShape.h"
#include "../../../../TonicEngine/Headers/Storage/ISerializable.h"

class DrawableComponent: public Component, public ISerializable {
public:
    DrawableComponent();
    ~DrawableComponent() override;
    std::unique_ptr<IShape> shape;
    std::vector<std::string> serialize() override;
};


#endif //PROJECT_SWA_DRAWABLECOMPONENT_H
