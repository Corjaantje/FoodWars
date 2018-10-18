//
// Created by Lucas on 11/10/2018.
//

#ifndef PROJECT_SWA_OTHERMENUSCREEN_H
#define PROJECT_SWA_OTHERMENUSCREEN_H

#include "memory"
#include "IScreen.h"
#include "ScreenStateManager.h"
#include "../../../TonicEngine/Headers/Visual/VisualFacade.h"

class OtherMenuScreen : public IScreen {
private:
    std::shared_ptr<VisualFacade> visualFacade;
    Renderlist _renderList;
public:
    OtherMenuScreen(std::shared_ptr<ScreenStateManager> context);
    ~OtherMenuScreen();
    void update(double deltaTime) override;
};

#endif //PROJECT_SWA_OTHERMENUSCREEN_H
