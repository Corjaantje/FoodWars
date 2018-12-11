#include "../../Headers/Storage/LevelStorage.h"
#include "../../../TonicEngine/Headers/Storage/XMLWriter.h"
#include "../../../TonicEngine/Headers/Storage/XMLReader.h"
#include "../../Headers/Storage/GameLevel/Impl/XMLGameLevelSerializeVisitor.h"
#include "../../Headers/Storage/GameLevel/Impl/XMLGameLevelDeserializeVisitor.h"
#include "../../Headers/GameECS/Components/PositionComponent.h"
#include "../../Headers/GameECS/Components/AnimationComponent.h"
#include "../../Headers/GameECS/Components/DamageableComponent.h"
#include "../../Headers/GameECS/Components/DamagingComponent.h"
#include "../../Headers/GameECS/Components/GravityComponent.h"
#include "../../Headers/GameECS/Components/JumpComponent.h"
#include "../../Headers/GameECS/Components/MoveComponent.h"
#include "../../Headers/GameECS/Components/PlayerComponent.h"
#include "../../Headers/GameECS/Components/TurnComponent.h"
#include "../../../TonicEngine/Headers/Visual/Colour.h"
#include "../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/ShapeRectangle.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/ShapeSprite.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/ShapeText.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/ShapeLine.h"

LevelStorage::LevelStorage() : _deserializationFactory{} {
    fillFactory(_deserializationFactory);
}

bool LevelStorage::saveLevel(const GameLevel &gameLevel, const std::string &toFile) {
    XMLWriter xmlWriter{};
    XMLGameLevelSerializeVisitor serializeVisitor{"Level"};
    serializeVisitor.visit(gameLevel);
    return xmlWriter.WriteXMLFile(serializeVisitor.getRootNode(), toFile);
}

bool LevelStorage::loadLevel(GameLevel &gameLevel, const std::string &file) {
    XMLReader xmlReader{};
    MyDocument doc = xmlReader.LoadFile(file);

    std::unordered_map<std::string, std::function<std::unique_ptr<SerializationReceiver>()>> _createFunctions;
    XMLGameLevelDeserializeVisitor deserializeVisitor{doc, _deserializationFactory};
    deserializeVisitor.visit(gameLevel);

    return false;
}

void LevelStorage::fillFactory(DeserializationFactory &factory) {
    factory.addType<Coordinate>();
    factory.addType<AnimationComponent>();
    factory.addType<DamageableComponent>();
    factory.addType<DrawableComponent>();
    factory.addType<DamagingComponent>();
    factory.addType<GravityComponent>();
    factory.addType<JumpComponent>();
    factory.addType<MoveComponent>();
    factory.addType<PlayerComponent>();
    factory.addType<PositionComponent>();
    factory.addType<TurnComponent>();
    factory.addType<BoxCollider>();
    factory.addType<Weapon>();
    factory.addType<ShapeRectangle>();
    factory.addType<ShapeSprite>();
    factory.addType<ShapeLine>();
    factory.addType<ShapeText>();
    factory.addType<Colour>();
}