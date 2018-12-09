#include "../../Headers/Storage/LevelStorage.h"
#include "../../../TonicEngine/Headers/Storage/XMLWriter.h"
#include "../../Headers/Storage/GameLevel/Impl/XMLGameLevelSerializeVisitor.h"

bool LevelStorage::saveLevel(const GameLevel &gameLevel, const std::string &toFile) {
    XMLWriter xmlWriter{};
    XMLGameLevelSerializeVisitor serializeVisitor{"Level"};
    serializeVisitor.visit("gameLevel", gameLevel);
    return xmlWriter.WriteXMLFile(serializeVisitor.getRootNode(), toFile);
}