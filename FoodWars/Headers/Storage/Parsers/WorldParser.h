#ifndef PROJECT_SWA_WORLDPARSER_H
#define PROJECT_SWA_WORLDPARSER_H

#include "BaseParser.h"
#include "../../GameECS/Entities/EntityManager.h"
#include "../../GameECS/Components/DrawableComponent.h"
#include "../../../../TonicEngine/Headers/Storage/XMLWriter.h"
#include "../../../../TonicEngine/Headers/Storage/XMLReader.h"

//TODO: shorten headers.
class WorldParser : public BaseParser<int> {
private:
    std::shared_ptr<EntityManager> _entityManager;
public:
    WorldParser();
    WorldParser(std::shared_ptr<EntityManager> ent);
    ~WorldParser();

    int* ParseFromXML(tinyxml2::XMLElement elem);
    void ParseToXML();

    MyDocument ParseDrawableComponents(MyDocument& my_doc, std::map<int, std::shared_ptr<DrawableComponent>> toSave);


};


#endif //PROJECT_SWA_WORLDPARSER_H
