#ifndef PROJECT_SWA_POWERUPCOMPONENT_H
#define PROJECT_SWA_POWERUPCOMPONENT_H

#include "Component.h"

class ItemComponent : public Component {
public:
    ItemComponent();
    ~ItemComponent() override;
public:
    void accept(SerializationVisitor &visitor) override;

    std::string getName() const override;
private:
    int _itemEffect;
    std::string _imageUrl;
};

#endif //PROJECT_SWA_POWERUPCOMPONENT_H
