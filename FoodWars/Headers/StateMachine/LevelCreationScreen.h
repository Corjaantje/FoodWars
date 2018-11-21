#ifndef PROJECT_SWA_LEVELEDITORSCREEN_H
#define PROJECT_SWA_LEVELEDITORSCREEN_H

#include "IScreen.h"
#include "ScreenStateManager.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/SpriteButton.h"
#include "Misc/LevelBuilder.h"

class LevelCreationScreen : public IScreen, public IObserver<KeyEvent>, public IObserver<MouseEvent> {
public:
    explicit LevelCreationScreen(std::shared_ptr<ScreenStateManager> context);
    ~LevelCreationScreen();
    void update(double deltaTime) override;
    void update(std::shared_ptr<KeyEvent> event) override;
    void update(std::shared_ptr<MouseEvent> event) override;

    SpriteButton* toggleCollidable = nullptr;
    SpriteButton* toggleDamageable = nullptr;

    SpriteButton* toggleBuildTerrain = nullptr;
    SpriteButton* toggleSetSpawn = nullptr;
    std::string selectedSong;
    bool buildTerrainActive = true;
private:
    void initButtons();
    void callRender();
    void relinkAndSave();

private:
    LevelBuilder _levelBuilder;
    std::shared_ptr<WindowResolutionCalculator> _windowResCalc;
};

#endif //PROJECT_SWA_LEVELEDITORSCREEN_H