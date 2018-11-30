#ifndef PROJECT_SWA_LEVELEDITORSCREEN_H
#define PROJECT_SWA_LEVELEDITORSCREEN_H

#include "IScreen.h"
#include "ScreenStateManager.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/SpriteButton.h"
#include "Misc/LevelBuilder.h"

class LevelCreationScreen : public IScreen, public IObserver<KeyEvent>, public IObserver<MouseEvent> {
public:
    LevelCreationScreen(ScreenStateManager& context);
    void update(double deltaTime) override;
    void update(const KeyEvent& event) override;
    void update(const MouseEvent& event) override;

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
    ShapeText* selectedSongText;
    LevelBuilder _levelBuilder;
    const FileManager* _fileManager;
};

#endif //PROJECT_SWA_LEVELEDITORSCREEN_H