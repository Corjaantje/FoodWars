//
// Created by Lucas on 11/10/2018.
//

#ifndef PROJECT_SWA_MAINMENUSCREEN_H
#define PROJECT_SWA_MAINMENUSCREEN_H

#include "IScreen.h"
#include "ScreenState.h"

class MainMenuScreen : public IScreen {
private:
    std::unique_ptr<VisualFacade> visualFacade;
    Renderlist _renderList;
public:
    MainMenuScreen(ScreenState *context);
    ~MainMenuScreen();
    void update(double deltaTime) const override;
};

#endif //PROJECT_SWA_MAINMENUSCREEN_H
