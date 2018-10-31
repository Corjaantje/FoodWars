#ifndef PROJECT_SWA_BUTTON_H
#define PROJECT_SWA_BUTTON_H

#include <string>
#include <functional>
#include "ShapeRectangle.h"
#include "ShapeText.h"
#include "../../Input/IObserver.h"
#include "../../Events/MouseEvent.h"
#include "../../Input/MouseEventObservable.h"

class Button : public ShapeRectangle, IObserver<MouseEvent> {
private:
    std::function<void()> _onClickFunction;
    std::string _text;
    ShapeText shapeText;
public:
    explicit Button(MouseEventObservable& mouseEventObservable);
    Button(MouseEventObservable& mouseEventObservable, const std::string& text, const std::function<void()>& onClick, int width, int height, int xPos, int yPos);
    Button(MouseEventObservable& mouseEventObservable, const std::string& text, const std::function<void()>& onClick, int width, int height, int xPos, int yPos, Colour buttonColour);
    Button(MouseEventObservable& mouseEventObservable, const std::string& text, const std::function<void()>& onClick, int width, int height, int xPos, int yPos, Colour buttonColour, Colour textColour);
    Button(MouseEventObservable& mouseEventObservable, const std::string& text, const std::function<void()>& onClick, int width, int height, int xPos, int yPos, int xOffSet, int yOffSet, Colour buttonColour, Colour textColour);

    void setXOffSet(int xOffSet);
    void setYOffSet(int yOffSet);
    void setText(const std::string& text);
    void setTextColor(const Colour& colour);
    void setButtonPosition(int x, int y);
    void setButtonColor(const Colour& colour);
    void setOnClickFunction(const std::function<void()>& onClick);

    void update(std::shared_ptr<MouseEvent> event) override;
    void addToRender(Renderlist* renderlist) override;
};

#endif //PROJECT_SWA_BUTTON_H
