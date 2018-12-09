//
// Created by Lucas on 15/10/2018.
//

#ifndef PROJECT_SWA_PRINTKEYINPUTOBSERVER_H
#define PROJECT_SWA_PRINTKEYINPUTOBSERVER_H

#include "../Events/KeyEvent.h"

class PrintKeyInputObserver : public IObserver<KeyEvent> {
public:
    PrintKeyInputObserver();

private:
    ~PrintKeyInputObserver();
    void update(KeyEvent& event);
};

#endif //PROJECT_SWA_PRINTKEYINPUTOBSERVER_H
