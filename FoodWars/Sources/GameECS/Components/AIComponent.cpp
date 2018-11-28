#include "../../../Headers/GameECS/Components/AIComponent.h"

AIComponent::AIComponent(int difficulty) : _difficulty(difficulty) {

}
int AIComponent::getDifficulty() const {
    return _difficulty;
}