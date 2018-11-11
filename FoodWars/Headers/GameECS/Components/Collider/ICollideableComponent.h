#ifndef PROJECT_SWA_ICOLLIDEABLECOMPONENT_H
#define PROJECT_SWA_ICOLLIDEABLECOMPONENT_H

#include "../Component.h"

class ICollideableComponent: public Component {
public:
    ~ICollideableComponent() override = default;
};

#endif //PROJECT_SWA_ICOLLIDEABLECOMPONENT_H
