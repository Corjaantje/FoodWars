#ifndef PROJECT_SWA_DRAWABLECOMPONENT_H
#define PROJECT_SWA_DRAWABLECOMPONENT_H


#include "Component.h"

class DrawableComponent: public Component {
public:
    DrawableComponent();
    ~DrawableComponent();
    void draw();
    int xPos;
    int yPos;

};


#endif //PROJECT_SWA_DRAWABLECOMPONENT_H
