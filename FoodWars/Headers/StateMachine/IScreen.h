#include <utility>

#ifndef PROJECT_SWA_ISCREEN_H
#define PROJECT_SWA_ISCREEN_H

#include "memory"

class ScreenStateManager;

class IScreen {
protected:
    std::shared_ptr<ScreenStateManager> _context;
public:

    IScreen(std::shared_ptr<ScreenStateManager> context) : _context(std::move(context)) {

    }

    ~IScreen() {

    }
    virtual void update(double deltaTime) {

    }
};
#endif //PROJECT_SWA_ISCREEN_H
