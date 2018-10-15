//
// Created by Lucas on 11/10/2018.
//
#ifndef PROJECT_SWA_ISCREEN_H
#define PROJECT_SWA_ISCREEN_H

class ScreenState;

class IScreen {
protected:
    ScreenState* _context;
public:

    IScreen(ScreenState* context) : _context(context) {

    }

    ~IScreen() {

    }
    virtual void update(double deltaTime) const {

    }
};
#endif //PROJECT_SWA_ISCREEN_H
