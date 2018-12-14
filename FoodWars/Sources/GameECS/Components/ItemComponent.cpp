#include "../../../Headers/GameECS/Components/ItemComponent.h"

ItemComponent::~ItemComponent() = default;

//TODO: Interface seggregation principle
void ItemComponent::accept(SerializationVisitor &visitor) {
    //visitor.visit("itemEffect", _itemEffect);
}

std::string ItemComponent::getName() const {
    return "ItemComponent";
}

ItemComponent::ItemComponent(const std::function<void(EntityManager &e, const CollisionEvent &event)> &lamda) : _lamdaOnCollision{lamda} {}

ItemComponent::ItemComponent(const ItemComponent &copy) : _lamdaOnCollision{copy._lamdaOnCollision} {}

const std::function<void(EntityManager &, const CollisionEvent &collisionEvent)> &ItemComponent::getLamda() const {
    return _lamdaOnCollision;
}