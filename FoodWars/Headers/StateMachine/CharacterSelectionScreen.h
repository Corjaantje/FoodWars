#ifndef PROJECT_SWA_CHARACTERSELECTIONSCREEN_H
#define PROJECT_SWA_CHARACTERSELECTIONSCREEN_H

#include "IScreen.h"
#include "Misc/CharacterBuilder.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/SpriteButton.h"

class CharacterSelectionScreen : public IScreen, public IObserver<KeyEvent> {
public:
    explicit CharacterSelectionScreen(ScreenStateManager& context, std::string selectedLevel);
    ~CharacterSelectionScreen() = default;
    void update(double deltaTime) override;
    void update(const KeyEvent& event) override;
private:
    void initButtons();
    void initImages();
    void setFactionColor(CharacterBuilder &builder, Faction faction);
private:
    std::string _selectedLevel;
    CharacterBuilder _playerOneBuilder;
    CharacterBuilder _playerTwoBuilder;
    SpriteButton* _togglePlayerTwoBot = nullptr;
    ShapeSprite* _leftPreview = nullptr;
    ShapeSprite* _rightPreview = nullptr;
    ShapeText* _selectedDifficulty = nullptr;

    unordered_map<Faction, string> _previewMapLeft;
    unordered_map<Faction, string> _previewMapRight;
    unordered_map<Difficulty , string> _difficultyMap;
};


#endif //PROJECT_SWA_CHARACTERSELECTIONSCREEN_H
