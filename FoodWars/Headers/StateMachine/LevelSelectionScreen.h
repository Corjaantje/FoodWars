#ifndef PROJECT_SWA_LEVELSELECTIONSCREEN_H
#define PROJECT_SWA_LEVELSELECTIONSCREEN_H

#include "IScreen.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/SpriteButton.h"
#include "../LevelManager.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/TextButton.h"


class LevelSelectionScreen : public IScreen, public IObserver<KeyEvent> {
public:
    explicit LevelSelectionScreen(std::shared_ptr<ScreenStateManager> context, std::shared_ptr<LevelManager> levelManager);
    ~LevelSelectionScreen();
    void update(double deltaTime) override;
    void update(std::shared_ptr<KeyEvent> event) override;

    void generateLevelButtons();
private:
    std::vector<std::string> _levels;
    std::vector<TextButton*> _levelButtons;
    int _currentIndex;
    std::shared_ptr<LevelManager> _levelManager;
    void swapLevels(bool directionNext);
};

#endif //PROJECT_SWA_LEVELSELECTIONSCREEN_H