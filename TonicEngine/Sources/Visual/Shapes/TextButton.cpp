#include <utility>

#include "../../../Headers/Visual/Shapes/TextButton.h"
#include "../../../Headers/Visual/Renderlist.h"

TextButton::TextButton(MouseEventObservable &mouseEventObservable) : ShapeRectangle(0,0,0,0, Colour{0,0,0,0}), shapeText(0,0,"",0,0,0,Colour{0,0,0,0}){
    mouseEventObservable.registerObserver(this);
}

TextButton::TextButton(MouseEventObservable& mouseEventObservable, const std::string &text, const std::function<void()>& onClick, int width, int height, int xPos, int yPos)
        : TextButton(mouseEventObservable, text, onClick, width, height, xPos, yPos, Colour{255,255,255,100}, Colour{0, 0, 0, 0}){
}

TextButton::TextButton(MouseEventObservable& mouseEventObservable, const std::string &text, const std::function<void()>& onClick, int width, int height, int xPos, int yPos,
               Colour colour) : TextButton(mouseEventObservable, text, onClick, width, height, xPos, yPos, colour, Colour{0, 0, 0, 0}){
}

TextButton::TextButton(MouseEventObservable &mouseEventObservable, const std::string &text,
               const std::function<void()> &onClick, int width, int height, int xPos, int yPos, Colour buttonColour,
               Colour textColour) : TextButton(mouseEventObservable, text, onClick, width, height, xPos, yPos, width/10, height/10, buttonColour, textColour){
}

TextButton::TextButton(MouseEventObservable &mouseEventObservable, const std::string &text,
        const std::function<void()> &onClick, int width, int height, int xPos, int yPos, int xOffSet,
        int yOffSet, Colour buttonColour, Colour textColour) :
        ShapeRectangle(width, height, xPos, yPos, buttonColour), _text(text), _onClickFunction(onClick),
        shapeText(xPos + xOffSet, yPos + yOffSet, _text, 180, width - (2 * xOffSet), height - (2 * yOffSet), textColour){
    mouseEventObservable.registerObserver(this);
}

/*TextButton::TextButton(MouseEventObservable &mouseEventObservable, const std::function<void()> &onClick, int width, int height, int xPos, int yPos, const std::string &imageURL) :
        ShapeRectangle(width, height, xPos, yPos, Colour{0,0,0,0}), shapeText(0,0,"",0,0,0,Colour{0,0,0,0}), shapeSprite(width, height, xPos, yPos, imageURL), _onClickFunction(onClick){
    mouseEventObservable.registerObserver(this);
}*/

void TextButton::addToRender(Renderlist *renderlist) {
    ShapeRectangle::addToRender(renderlist);
    shapeText.addToRender(renderlist);
}

void TextButton::update(std::shared_ptr<MouseEvent> event) {
    if((event->getXPosition() >= xPos && event->getXPosition() <= xPos + width)
       && (event->getYPosition() >= yPos && event->getYPosition() <= yPos + height) && event->getMouseEventType() == MouseEventType::Down)
        _onClickFunction();
}

void TextButton::setXOffSet(int xOffSet) {
    shapeText.xPos = this->xPos + xOffSet;
    shapeText.width = this->width - (2 * xOffSet);
}

void TextButton::setYOffSet(int yOffSet) {
    shapeText.yPos = this->yPos + yOffSet;
    shapeText.height = this->height - (2 * yOffSet);
}

void TextButton::setText(const std::string &text) {
    shapeText.text = text;
}

void TextButton::setTextColor(const Colour &colour) {
    shapeText.colour = colour;
}

void TextButton::setButtonPosition(int x, int y) {
    int xOffSet = (width - shapeText.width) / 2;
    int yOffSet = (height - shapeText.height) / 2;
    this->xPos = x;
    this->yPos = y;
    setXOffSet(xOffSet);
    setYOffSet(yOffSet);
}

void TextButton::setButtonColor(const Colour &colour) {
    this->colour = colour;
}

void TextButton::setOnClickFunction(const std::function<void()> &onClick) {
    this->_onClickFunction = onClick;
}

void TextButton::render(IRenderer &renderer) const {
    shapeText.render(renderer);
}
