#include "../../Headers/Storage/LevelStorage.h"
#include "../../../TonicEngine/Headers/Storage/XMLWriter.h"
#include "../../../TonicEngine/Headers/Storage/XMLReader.h"
#include "../../Headers/Storage/GameLevel/Impl/XMLGameLevelSerializeVisitor.h"
#include "../../Headers/Storage/GameLevel/Impl/XMLGameLevelDeserializeVisitor.h"

bool LevelStorage::saveLevel(const GameLevel &gameLevel, const std::string &toFile) {
    XMLWriter xmlWriter{};
    XMLGameLevelSerializeVisitor serializeVisitor{"Level"};
    serializeVisitor.visit(gameLevel);
    return xmlWriter.WriteXMLFile(serializeVisitor.getRootNode(), toFile);
}

bool LevelStorage::loadLevel(GameLevel &gameLevel, const std::string &file) {
    XMLReader xmlReader{};
    MyDocument doc = xmlReader.LoadFile(file);
    XMLGameLevelDeserializeVisitor deserializeVisitor{doc};
    deserializeVisitor.visit(gameLevel);

    return false;
}
