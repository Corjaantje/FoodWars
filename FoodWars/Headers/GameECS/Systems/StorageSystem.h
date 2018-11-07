#ifndef PROJECT_SWA_STORAGESYSTEM_H
#define PROJECT_SWA_STORAGESYSTEM_H

#include "../../../../TonicEngine/Headers/Storage/XMLReader.h"
#include "../../../../TonicEngine/Headers/Storage/XMLWriter.h"
#include "../../Storage/Parsers/WorldParser.h"
#include "IBaseSystem.h"

class StorageSystem{//}; : public IBaseSystem {
private:
    XMLReader _reader;
    XMLWriter _writer;
    std::shared_ptr<EntityManager> _entityManager;
public:
    StorageSystem();
    ~StorageSystem();

    void assignRelevantEntityManager(std::shared_ptr<EntityManager> entityManager);
    void saveWorld();
};


#endif //PROJECT_SWA_STORAGESYSTEM_H
