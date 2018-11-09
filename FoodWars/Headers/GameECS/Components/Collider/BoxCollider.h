#ifndef PROJECT_SWA_BOXCOLLIDER_H
#define PROJECT_SWA_BOXCOLLIDER_H

#include "ICollideableComponent.h"

class BoxCollider: public ICollideableComponent {
public:
    int width;
    int height;
    BoxCollider();
    BoxCollider(int width, int height);
    ~BoxCollider() override;
};
#endif //PROJECT_SWA_BOXCOLLIDER_H
