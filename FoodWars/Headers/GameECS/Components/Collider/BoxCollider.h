#ifndef PROJECT_SWA_BOXCOLLIDER_H
#define PROJECT_SWA_BOXCOLLIDER_H

#include "ICollideableComponent.h"
#include "../../../../../TonicEngine/Headers/Storage/ISerializable.h"

class BoxCollider: public ICollideableComponent, public ISerializable {
public:
    int width;
    int height;
    BoxCollider();
    BoxCollider(int width, int height);
    ~BoxCollider() override;
    std::vector<std::string> serialize() override;
};
#endif //PROJECT_SWA_BOXCOLLIDER_H
