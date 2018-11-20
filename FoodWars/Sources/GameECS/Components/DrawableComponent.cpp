#include <iostream>
#include "../../../Headers/GameECS/Components/DrawableComponent.h"

DrawableComponent::DrawableComponent() {

}


DrawableComponent::~DrawableComponent() {
    delete shape;
}
