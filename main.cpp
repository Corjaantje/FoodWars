#include <memory>

#include <ctime>
#include <afxres.h>
#include "TonicEngine/Headers/Visual/Window.h"
#include "TonicEngine/Headers/Visual/VisualFacade.h"
#include "TonicEngine/Headers/Input/InputFacade.h"
#include "TonicEngine/Headers/Input/PrintKeyInputObserver.h"
#include "TonicEngine/Headers/Input/PrintMouseInputObserver.h"
#include "TonicEngine/Headers/Audio/AudioFacade.h"
#include "FoodWars/Headers/GameECS/Entities/EntityManager.h"
#include "FoodWars/Headers/GameECS/Systems/DrawSystem.h"
#include "FoodWars/Headers/GameECS/Components/DrawableComponent.h"
#include "FoodWars/Headers/StateMachine/ScreenStateManager.h"
#include "TonicEngine/Headers/Communication/CommunicationFacade.h"
#include "FoodWars/Headers/StateMachine/MainMenuScreen.h"
#include "FoodWars/Headers/StateMachine/OtherMenuScreen.h"


int main(int argc, char** argv)
{
    VisualFacade* visualFacade = new VisualFacade();

    InputFacade inputFacade;
    inputFacade.getKeyEventObservable()->registerObserver(new PrintKeyInputObserver);
    inputFacade.getMouseEventObservable()->registerObserver(new PrintMouseInputObserver);

    visualFacade->setTitle("Food Wars");
    visualFacade->setResolution(640, 480);
    visualFacade->disablefullscreen();
    visualFacade->openWindow();

    std::shared_ptr<ScreenStateManager> screenStateManager = std::make_shared<ScreenStateManager>();
    screenStateManager->addFacade(visualFacade);
    screenStateManager->addOrSetScreenState(new MainMenuScreen(screenStateManager));
    screenStateManager->addOrSetScreenState(new OtherMenuScreen(screenStateManager));
    screenStateManager->setActiveScreen<MainMenuScreen>();

    //Config
    clock_t startProgramTime = clock();
    int maxMsProgramIsRunning = 10000; //Stop the program after 10 seconds
    double frameRateCap = 61;
    double amountOfUpdatesAllowedPerSecond = 1000.0 / frameRateCap; //= 16.666
    //End of config

    clock_t timeLast = clock();
    //Run the application only for MaxMSProgramIsRunning milliseconds.
    while((clock() - startProgramTime / CLOCKS_PER_SEC * 1000 < maxMsProgramIsRunning) && !inputFacade.isWindowClosed()) {
        inputFacade.pollEvents();
        double frameDelta = double (clock() - timeLast) / CLOCKS_PER_SEC * 1000.0;
        double deltaTime = 1/frameDelta;
        if(frameDelta > amountOfUpdatesAllowedPerSecond){
            screenStateManager->getCurrentState()->update(deltaTime);
            timeLast = clock();
        }

        if(clock() - startProgramTime / CLOCKS_PER_SEC * 1000 > 5000){
            screenStateManager->setActiveScreen<OtherMenuScreen>();
        }
    }
    return 0;
}

