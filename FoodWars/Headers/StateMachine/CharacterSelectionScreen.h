#ifndef PROJECT_SWA_CHARACTERSELECTIONSCREEN_H
#define PROJECT_SWA_CHARACTERSELECTIONSCREEN_H


#include "IScreen.h"
#include "Misc/CharacterBuilder.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/SpriteButton.h"

class CharacterSelectionScreen : public IScreen, public IObserver<KeyEvent> {
public:
    explicit CharacterSelectionScreen(ScreenStateManager& context, int levelIterator);
    ~CharacterSelectionScreen() = default;
    void update(double deltaTime) override;
    void update(const KeyEvent& event) override;
private:
    void initButtons();
    void initImages();
private:
    int _selectedLevelIterator;
    CharacterBuilder _playerOneBuilder;
    CharacterBuilder _playerTwoBuilder;
    SpriteButton* togglePlayerTwoBot = nullptr;
    ShapeSprite* _leftPreview = nullptr;
    ShapeSprite* _rightPreview = nullptr;

    unordered_map<FACTION, string> _previewMapLeft;
    unordered_map<FACTION, string> _previewMapRight;
};


#endif //PROJECT_SWA_CHARACTERSELECTIONSCREEN_H
