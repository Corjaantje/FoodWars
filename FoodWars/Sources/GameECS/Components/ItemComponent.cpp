#include "../../../Headers/GameECS/Components/ItemComponent.h"

ItemComponent::~ItemComponent() = default;

//TODO: Interface seggregation principle
void ItemComponent::accept(SerializationVisitor &visitor) {
    //visitor.visit("itemEffect", _itemEffect);
}

std::string ItemComponent::getName() const {
    return "ItemComponent";
}

ItemComponent::ItemComponent(std::string name, const std::function<void(EntityManager& e, const CollisionEvent &event)>& lamda) : _name{std::move(name)}, _lamdaOnCollision{&lamda} {}
ItemComponent::ItemComponent(const ItemComponent &copy) : _name{copy._name}, _lamdaOnCollision{copy._lamdaOnCollision} {}

const std::string &ItemComponent::getItemName() const {
    return _name;
}

const std::function<void(EntityManager &, const CollisionEvent &collisionEvent)>& ItemComponent::getLamda() const {
    return *_lamdaOnCollision;
}
