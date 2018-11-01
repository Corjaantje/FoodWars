#ifndef PROJECT_SWA_LEVELEDITORSCREEN_H
#define PROJECT_SWA_LEVELEDITORSCREEN_H

#include "IScreen.h"
#include "ScreenStateManager.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/SpriteButton.h"

class LevelEditorScreen : public IScreen, public IObserver<KeyEvent> {
public:
    explicit LevelEditorScreen(std::shared_ptr<ScreenStateManager> context);
    ~LevelEditorScreen();
    void update(double deltaTime) override;
    void update(std::shared_ptr<KeyEvent> event) override;
};

#endif //PROJECT_SWA_LEVELEDITORSCREEN_H