#ifndef PROJECT_SWA_LEVELSELECTIONSCREEN_H
#define PROJECT_SWA_LEVELSELECTIONSCREEN_H

#include "IScreen.h"
#include "../LevelManager.h"
#include "../../../TonicEngine/Headers/Storage/FileManager.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/SpriteButton.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/TextButton.h"


class LevelSelectionScreen : public IScreen, public IObserver<KeyEvent> {
public:
    LevelSelectionScreen(ScreenStateManager& context);
    ~LevelSelectionScreen();
    void update(double deltaTime) override;
    void update(const KeyEvent& event) override;

    void generateLevelButtons();
private:
    std::vector<std::string> _levels;
    std::vector<TextButton*> _levelButtons;
    int _currentIndex;
    void swapLevels(bool directionNext);
    MouseEventObservable* mouseEventObservable;
};

#endif //PROJECT_SWA_LEVELSELECTIONSCREEN_H