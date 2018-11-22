#include <memory>

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
#include "FoodWars/Headers/StateMachine/LoseTransitionScreen.h"
#include "FoodWars/Headers/StateMachine/WinTransitionScreen.h"
#include "FoodWars/Headers/StateMachine/DrawTransitionScreen.h"
#include "FoodWars/Headers/StateMachine/PauseScreen.h"
#include "FoodWars/Headers/StateMachine/HighscoreScreen.h"
#include "FoodWars/Headers/StateMachine/AdvertisingScreen.h"


int main(int argc, char** argv)
{
    std::shared_ptr<WindowResolutionCalculator> windowResolutionCalculator =  std::make_shared<WindowResolutionCalculator>();
    VisualFacade* visualFacade = new VisualFacade(windowResolutionCalculator);

    visualFacade->setTitle("Food Wars");
    visualFacade->setResolution(800, 450);
    visualFacade->disablefullscreen();
    visualFacade->openWindow();

    AudioFacade* audioFacade = new AudioFacade();
    audioFacade->setMusicVolume(5);
    audioFacade->setEffectVolume(10);

    GeneralFacade* generalFacade = new GeneralFacade();

    // Music
    audioFacade->addAudio("wildwest", "./Assets/Audio/wildwest.mp3");
    audioFacade->addAudio("menu", "./Assets/Audio/menu.mp3");
    audioFacade->addAudio("space", "./Assets/Audio/space.mp3");
    audioFacade->addAudio("space2", "./Assets/Audio/space2.mp3");
    audioFacade->addAudio("nature", "./Assets/Audio/nature.mp3");

    // Sound Effects
    audioFacade->addAudio("oof", "./Assets/Audio/oof.wav");
    audioFacade->addAudio("jump", "./Assets/Audio/jump.wav");

    std::shared_ptr<LevelManager> levelManager = std::make_shared<LevelManager>();
    AdvertisingManager advertisingManager = AdvertisingManager();
    std::shared_ptr<ScreenStateManager> screenStateManager = std::make_shared<ScreenStateManager>();
    InputFacade* inputFacade = new InputFacade();
    inputFacade->setWindowResolutionCalculator(windowResolutionCalculator);
    screenStateManager->setWindowResolutionCalculator(windowResolutionCalculator);
    screenStateManager->addFacade(visualFacade);
    screenStateManager->addFacade(inputFacade);
    screenStateManager->addFacade(audioFacade);
    screenStateManager->addOrSetScreenState(new MainMenuScreen(screenStateManager, advertisingManager));
    screenStateManager->addOrSetScreenState(new UpgradesScreen(screenStateManager));
    screenStateManager->addOrSetScreenState(new CreditScreen(screenStateManager));
    screenStateManager->addOrSetScreenState(new GameScreen(screenStateManager, new GameLevel()));
    screenStateManager->addOrSetScreenState(new LevelSelectionScreen(screenStateManager, levelManager));
    screenStateManager->addOrSetScreenState(new LevelCreationScreen(screenStateManager));
    screenStateManager->addOrSetScreenState(new HelpScreen(screenStateManager));
    screenStateManager->addOrSetScreenState(new SettingsScreen(screenStateManager));
    screenStateManager->addOrSetScreenState(new PauseScreen(screenStateManager));
    screenStateManager->addOrSetScreenState(new HighscoreScreen(screenStateManager));
    screenStateManager->addOrSetScreenState(new AdvertisingScreen(screenStateManager, advertisingManager));
    screenStateManager->addOrSetScreenState(new LoseTransitionScreen(screenStateManager));
    screenStateManager->addOrSetScreenState(new WinTransitionScreen(screenStateManager));
    screenStateManager->addOrSetScreenState(new DrawTransitionScreen(screenStateManager));

    screenStateManager->setActiveScreen<MainMenuScreen>();

    //Config
    double frameRateCap = 61.0;
    double amountOfUpdatesAllowedPerSecond = 1.0 / frameRateCap; //= 16.666
    //End of config

    double timeModifier = 1.0;
    // Modifier for changing the gameplay speed

    std::chrono::duration<double> timeLast = std::chrono::steady_clock::now().time_since_epoch();

    while(!screenStateManager->getCurrentState()->isWindowClosed()) {
        std::chrono::duration<double> currentTime = std::chrono::steady_clock::now().time_since_epoch();
        double deltaTime = (currentTime.count() - timeLast.count()) * timeModifier;
        if (deltaTime > 1) deltaTime = 1;
        timeLast = currentTime;
        screenStateManager->getCurrentState()->update(deltaTime);
        double sleepTime = amountOfUpdatesAllowedPerSecond * 1000 - deltaTime;
        if (sleepTime > 0.0)
            generalFacade->sleep(sleepTime);
    }
    delete generalFacade;
    return 0;
}

