#include "../../Headers/Storage/LevelStorage.h"
#include "../../../TonicEngine/Headers/Storage/XMLWriter.h"
#include "../../../TonicEngine/Headers/Storage/XMLReader.h"
#include "../../Headers/Storage/GameLevel/Impl/XMLGameLevelSerializeVisitor.h"
#include "../../Headers/Storage/GameLevel/Impl/XMLGameLevelDeserializeVisitor.h"
#include "../../Headers/GameECS/Components/PositionComponent.h"

bool LevelStorage::saveLevel(const GameLevel &gameLevel, const std::string &toFile) {
    XMLWriter xmlWriter{};
    XMLGameLevelSerializeVisitor serializeVisitor{"Level"};
    serializeVisitor.visit(gameLevel);
    return xmlWriter.WriteXMLFile(serializeVisitor.getRootNode(), toFile);
}

bool LevelStorage::loadLevel(GameLevel &gameLevel, const std::string &file) {
    XMLReader xmlReader{};
    MyDocument doc = xmlReader.LoadFile(file);
    DeserializationFactory factory{};
    factory.addType<Coordinate>();
    factory.addType<PositionComponent>();
    XMLGameLevelDeserializeVisitor deserializeVisitor{doc, factory};
    deserializeVisitor.visit(gameLevel);

    return false;
}
