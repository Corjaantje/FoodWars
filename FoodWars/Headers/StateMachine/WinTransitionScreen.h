#ifndef PROJECT_SWA_WINTRANSITIONSCREEN_H
#define PROJECT_SWA_WINTRANSITIONSCREEN_H

#include "LevelTransitionScreen.h"
#include "ScreenStateManager.h"

class WinTransitionScreen : public LevelTransitionScreen{
public:
    explicit WinTransitionScreen(ScreenStateManager& context);
    std::string getScreenName() const override;
};

#endif //PROJECT_SWA_WINTRANSITIONSCREEN_H