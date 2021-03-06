#include <memory>
#include <iostream>
#include "TonicEngine/Headers/Visual/VisualFacade.h"
#include "TonicEngine/Headers/Input/InputFacade.h"
#include "TonicEngine/Headers/Audio/AudioFacade.h"
#include "FoodWars/Headers/GameECS/Systems/DrawSystem.h"
#include "FoodWars/Headers/StateMachine/ScreenStateManager.h"
#include "FoodWars/Headers/StateMachine/MainMenuScreen.h"
#include "FoodWars/Headers/StateMachine/HelpScreen.h"
#include "FoodWars/Headers/StateMachine/CreditScreen.h"
#include "TonicEngine/Facades/GeneralFacade.h"

#include "FoodWars/Headers/StateMachine/UpgradesScreen.h"
#include "FoodWars/Headers/StateMachine/LevelTransitionScreen.h"
#include "FoodWars/Headers/StateMachine/PauseScreen.h"
#include "FoodWars/Headers/StateMachine/HighscoreScreen.h"
#include "FoodWars/Headers/StateMachine/AdvertisingScreen.h"
#include "TonicEngine/Headers/Storage/FileManager.h"



int main(int argc, char** argv)
{
    WindowResolutionCalculator windowResolutionCalculator {};
    VisualFacade visualFacade {windowResolutionCalculator};
    AudioFacade audioFacade{};
    GeneralFacade generalFacade{};

    LevelLoader levelManager{};
    FileManager fileManager{};
    ScreenStateManager screenStateManager{};

    visualFacade.setTitle("Food Wars");
    visualFacade.setResolution(800, 450);
    visualFacade.disablefullscreen();
    visualFacade.openWindow();

    for (auto const &file : fileManager.getFiles("./Assets/Audio/", {"mp3", "wav"}, true, true))
    {
        unsigned int startPos = file.find_last_of('/') + 1;
        std::string audioName = file.substr(startPos, file.find_last_of('.') - startPos);
        audioFacade.addAudio(audioName, file);
    }

    screenStateManager.setLevelManager(levelManager);
    screenStateManager.setWindowResolutionCalculator(windowResolutionCalculator);
    screenStateManager.addFacade(visualFacade);
    screenStateManager.addFacade(audioFacade);
    screenStateManager.setActiveScreen(std::make_unique<MainMenuScreen>(screenStateManager));

    //Config
    double frameRateCap = 61.0;
    double amountOfUpdatesAllowedPerSecond = 1.0 / frameRateCap; //= 16.666
    double timeModifier = 1.0;
    std::chrono::duration<double> timeLast = std::chrono::steady_clock::now().time_since_epoch();

    //framerate Update
    std::chrono::duration<double> timeLastFPS = std::chrono::steady_clock::now().time_since_epoch();
    int _updateCallCount = 0;
    //End of framerate update
    while(!screenStateManager.getCurrentState().isWindowClosed()) {
        _updateCallCount++;
        std::chrono::duration<double> currentTime = std::chrono::steady_clock::now().time_since_epoch();
        double deltaTime = (currentTime.count() - timeLast.count()) * timeModifier;
        if (deltaTime > 1) deltaTime = 1;
        timeLast = currentTime;
        screenStateManager.getCurrentState().update(deltaTime);
        double sleepTime = amountOfUpdatesAllowedPerSecond * 1000 - deltaTime;

        //framerate update
        std::chrono::duration<double> currentTimeFPS = std::chrono::steady_clock::now().time_since_epoch();
        double loggen = currentTimeFPS.count() - timeLastFPS.count();
        if (loggen >= 0.25) {
            if(_updateCallCount < 16){
                frameRateCap+= frameRateCap/8;
                amountOfUpdatesAllowedPerSecond = 1.0 / frameRateCap;
            }
            else{
                frameRateCap-= frameRateCap/16;
                amountOfUpdatesAllowedPerSecond = 1.0 / frameRateCap;
            }
            timeLastFPS = std::chrono::steady_clock::now().time_since_epoch();
            _updateCallCount = 0;
        }
        //End of framerate update

        if (sleepTime > 0.0)
            generalFacade.sleep(sleepTime);
    }
    return 0;
}

