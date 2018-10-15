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

    //Config
    clock_t startProgramTime = clock();
    int maxMsProgramIsRunning = 10000; //Stop the program after 10 seconds
    double frameRateCap = 60;
    double amountOfUpdatesAllowedPerSecond = 1000.0 / frameRateCap; //= 16.666
    //End of config

    clock_t timeLast = clock();
    //Run the application only for MaxMSProgramIsRunning milliseconds.
    while((clock() - startProgramTime / CLOCKS_PER_SEC * 1000 < maxMsProgramIsRunning) && !visualFacade->isWindowClosed()) {
        visualFacade->pollEvents();
        double frameDelta = double(clock() - timeLast) / CLOCKS_PER_SEC * 1000.0;
        double deltaTime = 1 / frameDelta;
        if (frameDelta > amountOfUpdatesAllowedPerSecond) {
            visualFacade->render();
            timeLast = clock();
        }
        //inputFacade.pollEvents();
    }
    return 0;
}

