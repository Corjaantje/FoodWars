#ifndef PROJECT_SWA_POWERUPCOMPONENT_H
#define PROJECT_SWA_POWERUPCOMPONENT_H

#include "Component.h"
#include "../Events/CollisionEventHandlerLamda.h"
#include "../Entities/EntityManager.h"

class ItemComponent : public Component {
public:
    ItemComponent(std::string name, const std::function<void(EntityManager&, const CollisionEvent& collisionEvent)>& lamda);
    ItemComponent(const ItemComponent& copy);
    ~ItemComponent() override;
public:
    void accept(SerializationVisitor &visitor) override;
    std::string getName() const override;
    const std::string& getItemName() const;
    const std::function<void(EntityManager&, const CollisionEvent& collisionEvent)>& getLamda() const;
private:
    std::string _name;
    const std::function<void(EntityManager&, const CollisionEvent& collisionEvent)>* _lamdaOnCollision;
};

#endif //PROJECT_SWA_POWERUPCOMPONENT_H
