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
    void update(std::shared_ptr<MouseEvent> event);
    void addToRender(Renderlist* renderlist) override;
    Button(MouseEventObservable& mouseEventObservable, const std::string& text, const std::function<void()>& onClick, int width, int height, int xPos, int yPos);
    Button(MouseEventObservable& mouseEventObservable, const std::string& text, const std::function<void()>& onClick, int width, int height, int xPos, int yPos, Colour colour);
};

#endif //PROJECT_SWA_BUTTON_H
