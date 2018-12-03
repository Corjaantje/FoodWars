#ifndef PROJECT_SWA_LEVELSELECTIONSCREEN_H
#define PROJECT_SWA_LEVELSELECTIONSCREEN_H

#include "IScreen.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/SpriteButton.h"
#include "../LevelLoader.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/TextButton.h"
#include "../../../TonicEngine/Headers/Storage/FileManager.h"

class LevelSelectionScreen : public IScreen, public IObserver<KeyEvent> {
public:
    explicit LevelSelectionScreen(std::shared_ptr<ScreenStateManager> context,
                                  std::shared_ptr<LevelLoader> levelManager,
                                  const FileManager& fileManager);
    ~LevelSelectionScreen();
    void update(double deltaTime) override;
    void update(std::shared_ptr<KeyEvent> event) override;

    void generateLevelButtons();
private:
    std::vector<std::string> _levels;
    std::vector<TextButton*> _levelButtons;
    int _currentIndex;
    std::shared_ptr<LevelLoader> _levelManager;
    void swapLevels(bool directionNext);
    MouseEventObservable* mouseEventObservable;
    const FileManager* _fileManager;
};

#endif //PROJECT_SWA_LEVELSELECTIONSCREEN_H