#ifndef PROJECT_SWA_POWERUPCOMPONENT_H
#define PROJECT_SWA_POWERUPCOMPONENT_H

#include "Component.h"
#include "../Events/CollisionEventHandlerLamda.h"
#include "../Entities/EntityManager.h"

class ItemComponent : public Component {
public:
    ItemComponent(const std::function<void(EntityManager&, const CollisionEvent& collisionEvent)>& lamda);
    ItemComponent(const ItemComponent& copy);
    /*ItemComponent& operator=(const ItemComponent& copy);
    ItemComponent& operator=(const ItemComponent&& move);
    ItemComponent(const ItemComponent&& move);*/ //todo!

    ~ItemComponent() override;
public:
    void accept(SerializationVisitor &visitor) override;
    std::string getName() const override;
    const std::function<void(EntityManager&, const CollisionEvent& collisionEvent)>& getLamda() const;
private:
    std::function<void(EntityManager&, const CollisionEvent& collisionEvent)> _lamdaOnCollision;
};

#endif //PROJECT_SWA_POWERUPCOMPONENT_H
