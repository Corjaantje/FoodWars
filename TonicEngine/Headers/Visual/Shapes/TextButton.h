#ifndef PROJECT_SWA_BUTTON_H
#define PROJECT_SWA_BUTTON_H

#include <string>
#include <functional>
#include "ShapeRectangle.h"
#include "ShapeSprite.h"
#include "ShapeText.h"
#include "../../Input/IObserver.h"
#include "../../Events/MouseEvent.h"
#include "../../Input/MouseEventObservable.h"

class TextButton : public ShapeRectangle, public IObserver<MouseEvent>{
private:
    MouseEventObservable *observable;
    std::function<void()> _onClickFunction;
protected:
    std::string _text;
    ShapeText shapeText;

public:
    explicit TextButton(MouseEventObservable& mouseEventObservable);
    TextButton(MouseEventObservable& mouseEventObservable, const std::string& text, const std::function<void()>& onClick, int width, int height, int xPos, int yPos);
    TextButton(MouseEventObservable& mouseEventObservable, const std::string& text, const std::function<void()>& onClick, int width, int height, int xPos, int yPos, Colour buttonColour);
    TextButton(MouseEventObservable& mouseEventObservable, const std::string& text, const std::function<void()>& onClick, int width, int height, int xPos, int yPos, Colour buttonColour, Colour textColour);
    TextButton(MouseEventObservable& mouseEventObservable, const std::string& text, const std::function<void()>& onClick, int width, int height, int xPos, int yPos, int xOffSet, int yOffSet, Colour buttonColour, Colour textColour);

    ~TextButton();

    void setXOffSet(int xOffSet);
    void setYOffSet(int yOffSet);
    void setText(const std::string& text);
    void setTextColor(const Colour& colour);
    void setButtonPosition(int x, int y);
    void setButtonColor(const Colour& colour);
    void setOnClickFunction(const std::function<void()>& onClick);

    void update(const MouseEvent& event) override;
    void addToRender(Renderlist* renderlist) override;

    void render(IRenderer &renderer) const override;
};

#endif //PROJECT_SWA_BUTTON_H
