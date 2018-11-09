#ifndef PROJECT_SWA_JUMPCOMPONENT_H
#define PROJECT_SWA_JUMPCOMPONENT_H

#include "Component.h"

class JumpComponent : public Component {
private:
    double _jumpAcceleration;
public:
    JumpComponent();
    JumpComponent(double acceleration);
    double getAcceleration() const;
    void setAcceleration(double acceleration);
};

#endif //PROJECT_SWA_JUMPCOMPONENT_H
