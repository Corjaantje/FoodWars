//
// Created by Lucas on 11/10/2018.
//

#ifndef PROJECT_SWA_MAINMENUSCREEN_H
#define PROJECT_SWA_MAINMENUSCREEN_H

#include "IScreen.h"
#include "ScreenStateManager.h"
#include "../../../TonicEngine/Headers/Events/MouseEvent.h"
#include "../../../TonicEngine/Headers/Input/IObserver.h"
#include "OtherMenuScreen.h"
#include "../../../TonicEngine/Headers/Input/InputFacade.h"


class MainMenuScreen : public IScreen, public IObserver<MouseEvent> {
private:
    std::shared_ptr<VisualFacade> visualFacade;
    std::shared_ptr<AudioFacade> audioFacade;
    InputFacade _inputFacade;
    Renderlist _renderList;
public:
    MainMenuScreen(std::shared_ptr<ScreenStateManager> context);
    ~MainMenuScreen();
    void update(double deltaTime) override;
    void update(std::shared_ptr<MouseEvent> event) override;
};

#endif //PROJECT_SWA_MAINMENUSCREEN_H
