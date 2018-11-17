#include <utility>

#include <utility>

#include "../../../Headers/Visual/Shapes/SpriteButton.h"
#include "../../../Headers/Visual/Renderlist.h"

SpriteButton::SpriteButton(MouseEventObservable &mouseEventObservable, const std::string &value,
                       const std::function<void()> &onClick, int width, int height, int xPos, int yPos, Colour buttonColour) :
        ShapeRectangle(width, height, xPos, yPos, buttonColour), _imageURL(value), _onClickFunction(onClick),
        shapeSprite(width, height, xPos, yPos, _imageURL){
    mouseEventObservable.registerObserver(this);
}

void SpriteButton::addToRender(Renderlist *renderlist) {
    ShapeRectangle::addToRender(renderlist);
    shapeSprite.addToRender(renderlist);
}

void SpriteButton::update(std::shared_ptr<MouseEvent> event) {
    if((event->getXPosition() >= xPos && event->getXPosition() <= xPos + width)
       && (event->getYPosition() >= yPos && event->getYPosition() <= yPos + height)  && event->getMouseEventType() == MouseEventType::Down)
        _onClickFunction();
}

void SpriteButton::render(IRenderer &renderer) const {
    shapeSprite.render(renderer);
}

void SpriteButton::changeImageURL(std::string url) {
    _imageURL = url;
    shapeSprite.imageURL = _imageURL;
}