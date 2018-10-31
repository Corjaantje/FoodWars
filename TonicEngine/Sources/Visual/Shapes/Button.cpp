#include <utility>

#include "../../../Headers/Visual/Shapes/Button.h"
#include "../../../Headers/Visual/Renderlist.h"

Button::Button(MouseEventObservable &mouseEventObservable) : ShapeRectangle(0,0,0,0, Colour{0,0,0,0}), shapeText(0,0,"",0,0,0,Colour{0,0,0,0}), shapeSprite(0, 0, 0, 0, "") {
    mouseEventObservable.registerObserver(this);
}

Button::Button(MouseEventObservable& mouseEventObservable, const std::string &text, const std::function<void()>& onClick, int width, int height, int xPos, int yPos) :
        Button(mouseEventObservable, text, onClick, width, height, xPos, yPos, Colour{255,255,255,100}, Colour{0, 0, 0, 0}){
}

Button::Button(MouseEventObservable& mouseEventObservable, const std::string &text, const std::function<void()>& onClick, int width, int height, int xPos, int yPos,
               Colour colour) : Button(mouseEventObservable, text, onClick, width, height, xPos, yPos, colour, Colour{0, 0, 0, 0}){
}

Button::Button(MouseEventObservable &mouseEventObservable, const std::string &text,
               const std::function<void()> &onClick, int width, int height, int xPos, int yPos, Colour buttonColour,
               Colour textColour) : Button(mouseEventObservable, text, onClick, width, height, xPos, yPos, width/10, height/10, buttonColour, textColour){
}

Button::Button(MouseEventObservable &mouseEventObservable, const std::string &text,
        const std::function<void()> &onClick, int width, int height, int xPos, int yPos, int xOffSet,
        int yOffSet, Colour buttonColour, Colour textColour) :
        ShapeRectangle(width, height, xPos, yPos, buttonColour), _text(text), _onClickFunction(onClick),
        shapeText(xPos + xOffSet, yPos + yOffSet, _text, 180, width - (2 * xOffSet), height - (2 * yOffSet), textColour), shapeSprite(0, 0, 0, 0, ""){
    mouseEventObservable.registerObserver(this);
}

Button::Button(MouseEventObservable &mouseEventObservable, const std::function<void()> &onClick, int width, int height, int xPos, int yPos, const std::string &imageURL) :
        ShapeRectangle(width, height, xPos, yPos, Colour{0,0,0,0}), shapeText(0,0,"",0,0,0,Colour{0,0,0,0}), shapeSprite(width, height, xPos, yPos, imageURL), _onClickFunction(onClick){
    mouseEventObservable.registerObserver(this);
}

void Button::addToRender(Renderlist *renderlist) {
    ShapeRectangle::addToRender(renderlist);
    shapeText.addToRender(renderlist);
    shapeSprite.addToRender(renderlist);
}

void Button::update(std::shared_ptr<MouseEvent> event) {
    if((event->getXPosition() >= xPos && event->getXPosition() <= xPos + width)
       && (event->getYPosition() >= yPos && event->getYPosition() <= yPos + height))
        _onClickFunction();
}

void Button::setXOffSet(int xOffSet) {
    shapeText.xPos = this->xPos + xOffSet;
    shapeText.width = this->width - (2 * xOffSet);
}

void Button::setYOffSet(int yOffSet) {
    shapeText.yPos = this->yPos + yOffSet;
    shapeText.height = this->height - (2 * yOffSet);
}

void Button::setText(const std::string &text) {
    shapeText.text = text;
}

void Button::setTextColor(const Colour &colour) {
    shapeText.colour = colour;
}

void Button::setButtonPosition(int x, int y) {
    int xOffSet = (width - shapeText.width) / 2;
    int yOffSet = (height - shapeText.height) / 2;
    this->xPos = x;
    this->yPos = y;
    setXOffSet(xOffSet);
    setYOffSet(yOffSet);
}

void Button::setButtonColor(const Colour &colour) {
    this->colour = colour;
}

void Button::setOnClickFunction(const std::function<void()> &onClick) {
    this->_onClickFunction = onClick;
}