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




    // Create audioFacade
    AudioFacade audioFacade;

    // Set volumes
    audioFacade.setMusicVolume(5);
    audioFacade.setEffectVolume(10);
    
    // Add Audio to _audioMap in the audioFacade
    audioFacade.addAudio("oof", "../FoodWars/Assets/Audio/oof.wav");
    audioFacade.addAudio("background", "../FoodWars/Assets/Audio/wildwest.wav");

    // Play background music
    audioFacade.playMusic("background", -1);

    // Play a sound effect
    audioFacade.playEffect("oof");




    while(!visualFacade->isWindowClosed()){
        visualFacade->render();
        visualFacade->pollEvents();
        //inputObservable->pollEvents();
    }
    /*WindowManager windowManager;
    windowManager.openWindow();
    nanogui::ref<Window> windowRef = nanogui::Screen(windowManager._window->getWindow(), Eigen::Vector2i(10, 10), "caption", true, false);
    SDL_Window* window = windowManager._window->getWindow();
    auto& button = window.add<nanogui::Button>("Plain button")
            .withCallback([] { std::cout << "pushed!" << std::endl; });*/



    return 0;
}
