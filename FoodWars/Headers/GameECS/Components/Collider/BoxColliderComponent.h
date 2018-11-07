#ifndef PROJECT_SWA_BOXCOLLIDER_H
#define PROJECT_SWA_BOXCOLLIDER_H

#include "ICollideableComponent.h"

class BoxColliderComponent: public ICollideableComponent {
public:
    int width;
    int height;
    BoxColliderComponent();
    BoxColliderComponent(int width, int height);
    ~BoxColliderComponent() override;
};
#endif //PROJECT_SWA_BOXCOLLIDER_H
