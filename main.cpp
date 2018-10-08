#include "TonicEngine/Headers/Visual/Window.h"
#include "TonicEngine/Headers/Visual/VisualFacade.h"
#include "TonicEngine/Headers/Input/InputObservable.h"
#include "TonicEngine/Headers/Audio/AudioFacade.h"

int main(int argc, char** argv)
{
    VisualFacade* visualFacade = new VisualFacade();
    InputObservable* inputObservable = new InputObservable();
    visualFacade->setTitle("Food Wars");
    //visualFacade->setResolution(1366, 768);
    visualFacade->setResolution(640, 480);
    visualFacade->disablefullscreen();
    ShapeRectangle rectangle(200, 200, 0, 0, Colour(0, 255, 0, 255));
    ShapeRectangle rectangle2(100, 100, 150, 150, Colour(0, 0, 255, 255));
    ShapeRectangle rectangle3(50, 50, 225, 225, Colour(255, 0, 0, 255));

    visualFacade->addRectangle(rectangle);
    visualFacade->addRectangle(rectangle2);
    visualFacade->addRectangle(rectangle3);

//    ShapeSprite sprite(150, 150, 200, 0, "../grass.bmp");
//    visualFacade->addSprite(sprite);
    visualFacade->openWindow();

    // Create AudioFacade
    AudioFacade audioFacade;

    // Play background music
    audioFacade.play("background");

    while(!visualFacade->isWindowClosed()){
        visualFacade->render();
        visualFacade->pollEvents();
        //inputObservable->pollEvents();
    }

    return 0;
}
