#include <memory>
#include <chrono>
#include <afxres.h>

#include "TonicEngine/Headers/Visual/Window.h"
#include "TonicEngine/Headers/Visual/VisualFacade.h"
#include "TonicEngine/Headers/Input/InputObservable.h"
#include "TonicEngine/Headers/Audio/AudioFacade.h"
#include "FoodWars/Headers/ScreenState.h"
#include "TonicEngine/Headers/Communication/CommunicationFacade.h"
#include "FoodWars/Headers/MainMenuScreen.h"
#include "FoodWars/Headers/OtherMenuScreen.h"


int main(int argc, char** argv)
{
    VisualFacade* visualFacade = new VisualFacade();
    visualFacade->setTitle("Food Wars");
    visualFacade->setResolution(640, 480);
    visualFacade->disablefullscreen();
    visualFacade->openWindow();

    AudioFacade* audioFacade = new AudioFacade();
    audioFacade->setMusicVolume(5);
    audioFacade->setEffectVolume(10);

    audioFacade->addAudio("oof", "../FoodWars/Assets/Audio/oof.wav");
    audioFacade->addAudio("wildwest", "../FoodWars/Assets/Audio/wildwest.wav");

    ScreenState screenState;
    screenState.addFacade(visualFacade);
    screenState.addFacade(new CommunicationFacade());
    screenState.addFacade(audioFacade);
    MainMenuScreen mainMenuScreen { &screenState };
    screenState.setState(&mainMenuScreen);

    int maxMsProgramIsRunning = 5000;
    int frameRateCap = 60;
    double maxDurationGameLoop = 1000.0 / frameRateCap;

    int updateCount = 0;
    clock_t startProgramTime = clock();
    while(clock() - startProgramTime / CLOCKS_PER_SEC * 1000 < maxMsProgramIsRunning) {
        clock_t start = clock();
        screenState.getCurrentState()->update(updateCount++); // tijden werken nog niet

        int updateDuration = double (clock() - start) / CLOCKS_PER_SEC * 1000.0;

        //std::cout << "Game Loop duratation: " << updateDuration << std::endl;
        if(maxDurationGameLoop - updateDuration > 0)
            Sleep(maxDurationGameLoop - updateDuration);
    }
    std::cout << "Total updates: " << updateCount << std::endl;
    return 0;
}
