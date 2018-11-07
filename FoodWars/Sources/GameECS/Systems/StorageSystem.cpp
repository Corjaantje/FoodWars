#include "../../../Headers/GameECS/Systems/StorageSystem.h"

StorageSystem::StorageSystem() {

}

StorageSystem::~StorageSystem() {

}

void StorageSystem::assignRelevantEntityManager(std::shared_ptr<EntityManager> entityManager) {
    _entityManager = entityManager;
}

void StorageSystem::saveWorld() {
    WorldParser worldParser {};
    MyNode rootNode {"root", nullptr};
    MyDocument myDoc { rootNode };

    myDoc = worldParser.ParseDrawableComponents(myDoc, _entityManager->getAllEntitiesWithComponent<DrawableComponent>());

    _writer.WriteXMLFile(myDoc, "warriorsOfTheWorld.xml");
}