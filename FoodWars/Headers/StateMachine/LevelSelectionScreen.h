#ifndef PROJECT_SWA_LEVELSELECTIONSCREEN_H
#define PROJECT_SWA_LEVELSELECTIONSCREEN_H

#include "IScreen.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/SpriteButton.h"
#include "../LevelLoader.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/TextButton.h"
#include "../../../TonicEngine/Headers/Storage/FileManager.h"

class LevelSelectionScreen : public IScreen, public IObserver<KeyEvent> {
public:
    explicit LevelSelectionScreen(ScreenStateManager& context);
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
    KeyEventObservable* keyEventObservable;
};

#endif //PROJECT_SWA_LEVELSELECTIONSCREEN_H