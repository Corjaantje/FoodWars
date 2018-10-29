#include <utility>

#include "../../../Headers/Visual/Shapes/Button.h"

Button::Button(MouseEventObservable& mouseEventObservable, const std::string &text, const std::function<void()>& onClick, int width, int height, int xPos, int yPos) :
    Button(mouseEventObservable, text, onClick, width, height, xPos, yPos, Colour{255,255,255,100}) {
}

Button::Button(MouseEventObservable& mouseEventObservable, const std::string &text, const std::function<void()>& onClick, int width, int height, int xPos, int yPos,
               Colour colour) :ShapeRectangle(width, height, xPos, yPos, colour), _text(text), _onClickFunction(onClick),
               shapeText(xPos + 10, yPos + 10, _text, 180, width - 20, height - 20, Colour{0, 0, 0, 0}){
    mouseEventObservable.registerObserver(this);
}

void Button::addToRender(Renderlist *renderlist) {
    ShapeRectangle::addToRender(renderlist);
    shapeText.addToRender(renderlist);
}

void Button::update(std::shared_ptr<MouseEvent> event) {
    if((event->getXPosition() >= xPos && event->getXPosition() <= xPos + width)
       && (event->getYPosition() >= yPos && event->getYPosition() <= yPos + height))
        _onClickFunction();
}
