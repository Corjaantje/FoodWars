#ifndef PROJECT_SWA_COMPONENTS_H
#define PROJECT_SWA_COMPONENTS_H

#include "../../../../TonicEngine/Headers/Storage/SerializationReceiver.h"

class Component : public SerializationReceiver {
public:
    Component();
    Component(const Component &other) = delete;
    virtual ~Component();
};

#endif //PROJECT_SWA_COMPONENTS_H