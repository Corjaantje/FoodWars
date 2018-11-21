#ifndef PROJECT_SWA_LOSETRANSITIONSCREEN_H
#define PROJECT_SWA_LOSETRANSITIONSCREEN_H

#include "LevelTransitionScreen.h"
#include "ScreenStateManager.h"

class LoseTransitionScreen : public LevelTransitionScreen {
public:
    explicit LoseTransitionScreen(std::shared_ptr<ScreenStateManager> context);
    std::string getScreenName() const override;
};


#endif //PROJECT_SWA_LOSETRANSITIONSCREEN_H
