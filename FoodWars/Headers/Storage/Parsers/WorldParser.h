#ifndef PROJECT_SWA_WORLDPARSER_H
#define PROJECT_SWA_WORLDPARSER_H

#include "BaseParser.h"
#include "../../GameECS/Entities/EntityManager.h"
#include "../../GameECS/Components/DrawableComponent.h"

class WorldParser : public BaseParser<int> {
private:
    std::shared_ptr<EntityManager> _entityManager;
public:
    WorldParser(std::shared_ptr<EntityManager> ent);
    ~WorldParser();

    // Maybe just ignore the base class aspect? At least until a decent image is formed for the returntype?
    int* ParseFromXML(tinyxml2::XMLElement elem);
    void ParseToXML();
};


#endif //PROJECT_SWA_WORLDPARSER_H
