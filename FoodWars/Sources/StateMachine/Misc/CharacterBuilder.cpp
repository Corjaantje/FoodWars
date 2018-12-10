#include "../../../Headers/StateMachine/Misc/CharacterBuilder.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/ShapeSprite.h"
#include "../../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../../Headers/GameECS/Components/TurnComponent.h"
#include "../../../Headers/GameECS/Components/GravityComponent.h"
#include "../../../Headers/GameECS/Components/MoveComponent.h"
#include "../../../Headers/GameECS/Components/AnimationComponent.h"
#include "../../../Headers/GameECS/Components/DamageableComponent.h"
#include "../../../Headers/GameECS/Components/PlayerComponent.h"
#include "../../../Headers/GameECS/Components/AIComponent.h"

bool CharacterBuilder::getIsBot() const {
    return _isBot;
}

const void CharacterBuilder::setIsBot(bool state) {
    _isBot = state;
}

Faction CharacterBuilder::getFaction() const {
    return _faction;
}

const void CharacterBuilder::setFaction(Faction faction) {
    _faction = faction;
}

Difficulty CharacterBuilder::getDifficulty() const {
    return _botDifficulty;
}

void CharacterBuilder::increaseDifficulty() {
    _botDifficulty = static_cast<Difficulty>((_botDifficulty + 1) % (3));
}

void CharacterBuilder::decreaseDifficulty() {
    if(_botDifficulty - 1 < 0){
        _botDifficulty = static_cast<Difficulty>(2);
    }
    else{
        _botDifficulty = static_cast<Difficulty>(_botDifficulty - 1);

    }
}

void CharacterBuilder::buildCharacterEntity(GameLevel &gameLevel, int playerID, int spawnX, int spawnY,
                                            bool startTurn) {
    std::vector<std::unique_ptr<IShape>> spawnAnimation;
    spawnAnimation.push_back(std::make_unique<ShapeSprite>(48, 72, spawnX, spawnY, ""));

    EntityManager *entityManager = &gameLevel.getEntityManager();
    int player = entityManager->createEntity();
    entityManager->addComponentToEntity<DrawableComponent>(player, std::make_unique<ShapeSprite>(48, 72,
                                                                                                 spawnX,
                                                                                                 spawnY,
                                                                                                 ""));
    entityManager->addComponentToEntity<BoxCollider>(player, 48, 72);
    entityManager->addComponentToEntity<PositionComponent>(player, spawnX, spawnY);
    auto &turnComponent = entityManager->addComponentToEntity<TurnComponent>(player);
    entityManager->addComponentToEntity<MoveComponent>(player);
    entityManager->addComponentToEntity<GravityComponent>(player);
    entityManager->addComponentToEntity<AnimationComponent>(player, std::move(spawnAnimation), 0.1);
    entityManager->addComponentToEntity<DamageableComponent>(player);
    entityManager->addComponentToEntity<PlayerComponent>(player, playerID, getFaction());
    if (startTurn) {
        turnComponent.switchTurn(true);
        turnComponent.setRemainingTime(30);
    }
    if (getIsBot()) {
        entityManager->addComponentToEntity<AIComponent>(player, _botDifficulty);
    }
}