#include "../../../Headers/GameECS/Components/ItemComponent.h"

ItemComponent::ItemComponent() : _itemEffect{0} {

}

ItemComponent::~ItemComponent() = default;

void ItemComponent::accept(SerializationVisitor &visitor) {
    visitor.visit("itemEffect", _itemEffect);
}

std::string ItemComponent::getName() const {
    return "ItemComponent";
}

std::string ItemComponent::getImage() const {
    return _imageUrl;
}

void ItemComponent::setImage(std::string imageUrl) {
    _imageUrl = imageUrl;
}
