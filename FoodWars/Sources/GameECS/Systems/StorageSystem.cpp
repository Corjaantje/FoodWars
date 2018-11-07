#include "../../../Headers/GameECS/Systems/StorageSystem.h"

StorageSystem::StorageSystem() {
//    _storageFacade =
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

    // DrawableComponent
    // GravityComponent
    // MoveComponent
    // PositionComponent
    // TurnComponent
    myDoc = worldParser.ParseDrawableComponents(myDoc, _entityManager->getAllEntitiesWithComponent<DrawableComponent>());



    /*
     * "Iserializable" aanmaken in engine
        Components laten implementeren
        Als je "serialize" aanroept dan moeten de components hun gegevens teruggeven

        Game dingen > StorageSystem > XMLFacade > XMLReader/Writer?
        Zelf map bijhouden <int(entity id), MyNode>
        Child nodes aan MyNode hangen

        Vraag steeds "getallentitieswithcomponent" bvb movecomponent
        Heb ik al entity met dit ID in mijn map?
        Zo ja: voeg toe als child
        Zo nee: maak nieuwe, voeg toe als child
     */
    _writer.WriteXMLFile(myDoc, "LevelOne.xml");
}

bool StorageSystem::loadWorld() {



    return false;
}
