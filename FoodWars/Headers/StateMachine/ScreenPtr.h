//
// Created by Lucas on 11/10/2018.
//

#ifndef PROJECT_SWA_SCREENPTR_H
#define PROJECT_SWA_SCREENPTR_H

#include "IScreen.h"

class ScreenPtr {
private:
const IScreen *_screen;
public:
    explicit ScreenPtr(const IScreen* screen);

    ~ScreenPtr();

    ScreenPtr(const ScreenPtr& other);

    ScreenPtr& operator=(const ScreenPtr& other) ;

    ScreenPtr(ScreenPtr&& other) noexcept;

    ScreenPtr& operator=(ScreenPtr&& other) noexcept;

    void update(double deltaTime) const;

};

#endif //PROJECT_SWA_SCREENPTR_H
