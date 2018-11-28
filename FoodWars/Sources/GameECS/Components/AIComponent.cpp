#include "../../../Headers/GameECS/Components/AIComponent.h"

AIComponent::AIComponent(int id, int difficulty) : PlayerComponent(id), _difficulty(difficulty) {

}

int AIComponent::getDifficulty() const {
    return _difficulty;
}
