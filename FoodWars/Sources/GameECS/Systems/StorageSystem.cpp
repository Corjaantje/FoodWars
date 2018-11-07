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


    // map[0] > <EntityID> as base
    //            <DrawComponent>
    //              DrawCompData
    //            </DrawComponent>
    //          </EntityID>
    // map[1] >
    // map[2] >
    // map[3] >
    // map[4] >
    // map[5] >
    // map[6] >
    std::map<int, MyNode> allComponents { std::map<int, MyNode>() };
//    MyNode drawNodes { "drawcomponent", &rootNode };

    std::map<int, std::shared_ptr<DrawableComponent>> components {_entityManager->getAllEntitiesWithComponent<DrawableComponent>()};
    // Can probably move this to a function with a <T> and pass a name for the newDraw?
    // Would just need an array of the kinds of components.
    for (auto const& drawComp : components)
    {
        // If there is a component with this ID
        if (allComponents.count(drawComp.first))
        {
            // Gets the "base" of the structure for this EntityID
            MyNode newDraw { "drawcomponent", allComponents[drawComp.first].FirstChildElement()};

            allComponents[drawComp.first].FirstChildElement()->AddChild(newDraw);

//            allComponents[drawComp.first].AddChild(newDraw);
        }
        else
        {
            MyNode newID { std::to_string(drawComp.first), &rootNode};

            MyNode newDraw { "drawcomponent", &newID};

            newID.AddChild(newDraw);
            allComponents[drawComp.first] = newID;
        }
    }

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
