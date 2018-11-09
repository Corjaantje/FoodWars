#include "../../../Headers/GameECS/Systems/StorageSystem.h"

StorageSystem::StorageSystem() {
//    _storageFacade =
}

StorageSystem::~StorageSystem() {

}

template<typename Comp>
void StorageSystem::addComponentTypeOf(std::string compName, map<int, MyNode> &foundComponents, MyNode &rootNode) {

    std::map<int, std::shared_ptr<DrawableComponent>> components {_entityManager->getAllEntitiesWithComponent<DrawableComponent>()};
    // Can probably move this to a function with a <T> and pass a name for the newDraw?
    // Would just need an array of the kinds of components.
    for (auto const& drawComp : components)
    {
        // If there is a component with this ID
        if (foundComponents.count(drawComp.first))
        {
            // Gets the "base" of the structure for this EntityID
            MyNode newDraw { compName, foundComponents[drawComp.first].FirstChildElement()};

            foundComponents[drawComp.first].FirstChildElement()->AddChild(newDraw);

//            allComponents[drawComp.first].AddChild(newDraw);
        }
        else
        {
            MyNode newID { std::to_string(drawComp.first), &rootNode};

            MyNode newDraw { compName, &newID};

            newID.AddChild(newDraw);
            foundComponents[drawComp.first] = newID;
        }
    }
}

void StorageSystem::saveDrawables() {

}

void StorageSystem::saveGravity() {

}

void StorageSystem::saveMove() {

}

void StorageSystem::savePosition() {

}

void StorageSystem::saveturns() {

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

//    std::map<string, Comp> compTypes;
//    compTypes["drawcomponent"] = DrawableComponent();
//    compTypes["gravitycomponent"] = GravityComponent();
//    compTypes["movecomponent"] = MoveComponent();
//    compTypes["positioncomponent"] = PositionComponent();
//    compTypes["turncomponent"] = TurnComponent();
//
//
//    for (auto const& types : compTypes)
//    {
//
//        std::map<int, std::shared_ptr<types.second>> compownent {_entityManager->getAllEntitiesWithComponent<types.second>()};
//        std::map<int, std::shared_ptr<DrawableComponent>> components {_entityManager->getAllEntitiesWithComponent<DrawableComponent>()};
//
//    }

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
    // what if I just get all of the entity IDs and work from there?
    std::map<int, int> allEntityIDs { std::map<int, int>() };
//    DrawableComponent();
//    GravityComponent();
//    MoveComponent();
//    PositionComponent();
//    TurnComponent();
    std::map<int, std::shared_ptr<DrawableComponent>> draws {_entityManager->getAllEntitiesWithComponent<DrawableComponent>()};
    std::map<int, std::shared_ptr<GravityComponent>> gravs {_entityManager->getAllEntitiesWithComponent<GravityComponent>()};
    std::map<int, std::shared_ptr<MoveComponent>> moves {_entityManager->getAllEntitiesWithComponent<MoveComponent>()};
    std::map<int, std::shared_ptr<PositionComponent>> positions {_entityManager->getAllEntitiesWithComponent<PositionComponent>()};
    std::map<int, std::shared_ptr<TurnComponent>> turns {_entityManager->getAllEntitiesWithComponent<TurnComponent>()};

    vector<int> entityIDs;
    for (auto const& comp : draws)
    {   if (std::find(entityIDs.begin(), entityIDs.end(), comp.first) != entityIDs.end()) {
            entityIDs.push_back(comp.first);
        }
    }
    for (auto const& comp : gravs)
    {   if (std::find(entityIDs.begin(), entityIDs.end(), comp.first) != entityIDs.end()) {
            entityIDs.push_back(comp.first);
        }
    }
    for (auto const& comp : moves)
    {   if (std::find(entityIDs.begin(), entityIDs.end(), comp.first) != entityIDs.end()) {
            entityIDs.push_back(comp.first);
        }
    }
    for (auto const& comp : positions)
    {   if (std::find(entityIDs.begin(), entityIDs.end(), comp.first) != entityIDs.end()) {
            entityIDs.push_back(comp.first);
        }
    }
    for (auto const& comp : turns)
    {   if (std::find(entityIDs.begin(), entityIDs.end(), comp.first) != entityIDs.end()) {
            entityIDs.push_back(comp.first);
        }
    }
     */
    // I'd need something filthy to distinguish between types? Or I'd implement that ISerializable suggestion...



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

    // DrawableComponent: can't get the color yet
    // MoveComponent: Worth it to save the PositionComponent as well?

    _writer.WriteXMLFile(myDoc, "LevelOne.xml");
}

bool StorageSystem::loadWorld() {



    return false;
}
