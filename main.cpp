#include <ctime>
#include <afxres.h>
#include "TonicEngine/Headers/Visual/Window.h"
#include "TonicEngine/Headers/Visual/VisualFacade.h"
#include "TonicEngine/Headers/Input/InputObservable.h"
#include "TonicEngine/Headers/Audio/AudioFacade.h"
#include "FoodWars/Headers/GameECS/Entities/EntityManager.h"
#include "FoodWars/Headers/GameECS/Systems/DrawSystem.h"
#include "FoodWars/Headers/GameECS/Components/DrawableComponent.h"
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

    ScreenState screenState;
    screenState.addFacade(visualFacade);
    MainMenuScreen mainMenuScreen { &screenState };
    OtherMenuScreen otherMenuScreen { &screenState};
    screenState.setState(&mainMenuScreen);
    //Config
    clock_t startProgramTime = clock();
    int maxMsProgramIsRunning = 10000; //Stop the program after 10 seconds
    double frameRateCap = 61;
    double amountOfUpdatesAllowedPerSecond = 1000.0 / frameRateCap; //= 16.666
    //End of config

    clock_t timeLast = clock();
    //Run the application only for MaxMSProgramIsRunning milliseconds.
    while((clock() - startProgramTime / CLOCKS_PER_SEC * 1000 < maxMsProgramIsRunning) && !visualFacade->isWindowClosed()) {
        visualFacade->pollEvents();
        double frameDelta = double (clock() - timeLast) / CLOCKS_PER_SEC * 1000.0;
        double deltaTime = 1/frameDelta;
        if(frameDelta > amountOfUpdatesAllowedPerSecond){
            screenState.getCurrentState()->update(deltaTime);
            timeLast = clock();
        }

        if(clock() - startProgramTime / CLOCKS_PER_SEC * 1000 > 5000){
            screenState.setState(&otherMenuScreen);
        }
    }

    return 0;
}
