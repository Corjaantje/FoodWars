#ifndef PROJECT_SWA_BOXCOLLIDER_H
#define PROJECT_SWA_BOXCOLLIDER_H

#include "ICollideableComponent.h"
#include "../../../../../TonicEngine/Headers/Storage/ISerializable.h"

class BoxCollider : public ICollideableComponent {
public:
    int width;
    int height;
    int isVirtual;
    BoxCollider();
    BoxCollider(int width, int height);

    BoxCollider(int width, int height, bool isVirtual);
    ~BoxCollider() override;

    void accept(SerializationVisitor &visitor) override;

    std::string getName() const override;
};
#endif //PROJECT_SWA_BOXCOLLIDER_H
