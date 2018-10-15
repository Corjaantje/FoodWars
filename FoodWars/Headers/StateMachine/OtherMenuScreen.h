//
// Created by Lucas on 11/10/2018.
//

#ifndef PROJECT_SWA_OTHERMENUSCREEN_H
#define PROJECT_SWA_OTHERMENUSCREEN_H

#include "memory"
#include "IScreen.h"
#include "ScreenState.h"
#include "../../../TonicEngine/Headers/Visual/VisualFacade.h"

class OtherMenuScreen : public IScreen {
private:
    std::unique_ptr<VisualFacade> visualFacade;
public:
    OtherMenuScreen(ScreenState *context);
    ~OtherMenuScreen();
    void update(double deltaTime) const override;
};

#endif //PROJECT_SWA_OTHERMENUSCREEN_H
