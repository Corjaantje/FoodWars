#ifndef PROJECT_SWA_DRAWABLECOMPONENT_H
#define PROJECT_SWA_DRAWABLECOMPONENT_H


#include <bits/unique_ptr.h>
#include "Component.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/IShape.h"

class DrawableComponent: public Component {
public:
    DrawableComponent();
    ~DrawableComponent() override;
    std::unique_ptr<IShape> shape;
};


#endif //PROJECT_SWA_DRAWABLECOMPONENT_H
