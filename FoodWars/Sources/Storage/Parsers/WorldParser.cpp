#include "../../../Headers/Storage/Parsers/WorldParser.h"

WorldParser::WorldParser(std::shared_ptr<EntityManager> ent) {
    _entityManager = ent;
}

int* WorldParser::ParseFromXML(tinyxml2::XMLElement elem) {
    //TODO: Make actual loading function
    return 0;
}

void WorldParser::ParseToXML() {
    std::map<int, std::shared_ptr<DrawableComponent>> toSave {_entityManager->getAllEntitiesWithComponent<DrawableComponent>()};


    for (auto const& drawComp : toSave)
    {

    }
}


