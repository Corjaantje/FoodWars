#ifndef PROJECT_SWA_SPRITEBUTTON_H
#define PROJECT_SWA_SPRITEBUTTON_H

#include <string>
#include <functional>
#include "ShapeRectangle.h"
#include "ShapeSprite.h"
#include "../../Input/IObserver.h"
#include "../../Events/MouseEvent.h"
#include "../../Input/MouseEventObservable.h"

class SpriteButton : public ShapeRectangle, IObserver<MouseEvent>{
private:
    std::function<void()> _onClickFunction;
    std::string _imageURL;
    ShapeSprite shapeSprite;
public:
    SpriteButton(MouseEventObservable& mouseEventObservable, const std::string& value, const std::function<void()>& onClick, int width, int height, int xPos, int yPos, Colour buttonColour);
    void changeImageURL(std::string url);
    void update(std::shared_ptr<MouseEvent> event) override;
    void addToRender(Renderlist* renderlist) override;
};

#endif //PROJECT_SWA_SPRITEBUTTON_H