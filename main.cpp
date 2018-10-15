#include "TonicEngine/Headers/Visual/Window.h"
#include "TonicEngine/Headers/Visual/VisualFacade.h"
#include "TonicEngine/Headers/Input/InputFacade.h"
#include "TonicEngine/Headers/Input/PrintKeyInputObserver.h"
#include "TonicEngine/Headers/Input/PrintMouseInputObserver.h"

int main(int argc, char** argv)
{
    VisualFacade* visualFacade = new VisualFacade();

    InputFacade inputFacade;
    inputFacade.getKeyEventObservable()->registerObserver(new PrintKeyInputObserver);
    inputFacade.getMouseEventObservable()->registerObserver(new PrintMouseInputObserver);

    visualFacade->setTitle("Food Wars");
    //visualFacade->setResolution(1366, 768);
    visualFacade->setResolution(640, 480);
    visualFacade->disablefullscreen();
    ShapeRectangle rectangle(150, 150, 0, 0, Colour(0, 255, 0, 255));
    ShapeRectangle rectangle2(75, 75, 150, 150, Colour(0, 0, 255, 255));
    visualFacade->addRectangle(rectangle);
    visualFacade->addRectangle(rectangle2);
    ShapeSprite sprite(150, 150, 200, 0, "../grass.bmp");
    visualFacade->addSprite(sprite);
    visualFacade->openWindow();

    while(!visualFacade->isWindowClosed()){
        visualFacade->render();
        //visualFacade->pollEvents();
        inputFacade.pollEvents();
    }

//    // Sound
//    SDL_Init(SDL_INIT_AUDIO);
//    AudioFacade effect{};
//    AudioFacade background{};
//
//    // Locatie is vanaf de exe file
//    // background
//    background.load("../FoodWars/Assets/Audio/wildwest.wav");
//    background.play();
//
//    SDL_Delay(5600);
//    // oof
//    effect.load("../FoodWars/Assets/Audio/oof.wav");
//    effect.play();
//    SDL_Delay(500);
//    effect.play();
//    SDL_Delay(500);
//    effect.play();
//    SDL_Delay(500);
//    effect.play();
//    SDL_Delay(10000);

    return 0;
}
