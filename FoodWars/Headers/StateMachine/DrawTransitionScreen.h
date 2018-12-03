#ifndef PROJECT_SWA_DRAWTRANSITIONSCREEN_H
#define PROJECT_SWA_DRAWTRANSITIONSCREEN_H

#include "LevelTransitionScreen.h"
#include "ScreenStateManager.h"

class DrawTransitionScreen : public LevelTransitionScreen {
public:
    explicit DrawTransitionScreen(ScreenStateManager& context);
    std::string getScreenName() const override;
};


#endif //PROJECT_SWA_DRAWTRANSITIONSCREEN_H
