#ifndef PROJECT_SWA_GRAVITYCOMPONENT_H
#define PROJECT_SWA_GRAVITYCOMPONENT_H

#include "Component.h"
#include "../../../../TonicEngine/Headers/Storage/ISerializable.h"

class GravityComponent : public Component, public ISerializable {
public:
    double gravityApplied;
    GravityComponent();
    std::vector<std::string> serialize() override;
};

#endif //PROJECT_SWA_GRAVITYCOMPONENT_H
