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

void StorageSystem::addDrawables(MyNode& myNode, std::shared_ptr<DrawableComponent> toSave) {
    std::vector<std::string> filling = toSave->serialize();

    MyNode drawNode{ filling[0], &myNode};

    // Gathering values of the position
    MyNode positionNode { "position", &drawNode};

    MyNode xPos { "xpos", &positionNode};
    xPos.SetValue(filling[1]);
    MyNode yPos { "ypos", &positionNode};
    yPos.SetValue(filling[2]);

    positionNode.AddChild(yPos);
    positionNode.AddChild(xPos);

    // Gathering values of the "shape"
    MyNode shapeNode { "shape", &drawNode};

    MyNode widthNode { "height", &shapeNode };
    widthNode.SetValue(filling[3]);
    MyNode heightNode { "width", &shapeNode };
    heightNode.SetValue(filling[4]);
    // MyNode colorNode { "color", &shape_node };
    // colorNode.SetValue(IDK MAN)

    shapeNode.AddChild(widthNode);
    shapeNode.AddChild(heightNode);
    //shape_node.AddChild(colorNode);



    drawNode.AddChild(shapeNode);
    drawNode.AddChild(positionNode);

    myNode.AddChild(drawNode);
}

void StorageSystem::addGravity(MyNode& my_doc, std::shared_ptr<GravityComponent> toSave) {

}

void StorageSystem::addMove(MyNode& my_doc, std::shared_ptr<MoveComponent> toSave) {

}

void StorageSystem::addPosition(MyNode& my_doc, std::shared_ptr<PositionComponent> toSave) {

}

void StorageSystem::addTurns(MyNode& my_doc, std::shared_ptr<TurnComponent> toSave) {

}

void StorageSystem::assignRelevantEntityManager(std::shared_ptr<EntityManager> entityManager) {
    _entityManager = entityManager;
}

void StorageSystem::saveWorld() {
    WorldParser worldParser {};
    MyNode initialRootNode {"root", nullptr};
    MyDocument initialMyDoc { initialRootNode };

    // DrawableComponent
    // GravityComponent
    // MoveComponent
    // PositionComponent
    // TurnComponent
    initialMyDoc = worldParser.ParseDrawableComponents(initialMyDoc, _entityManager->getAllEntitiesWithComponent<DrawableComponent>());

    std::string test1;
    test1 = "This code works, right?";

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

/*
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
*/
//    WorldParser worldParser {};
    MyNode trueRootNode {"root", nullptr};
    MyDocument myDoc { trueRootNode };

    // what if I just get all of the entity IDs and work from there?
    std::map<int, MyNode&> IDNodes { std::map<int, MyNode&>() };
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
    std::map<int, int> nodeLocations;
    vector<MyNode*> nodeIDs;
    for (auto const& comp : draws)
    {
        // Check if the Entity ID already exists
        if (std::find(entityIDs.begin(), entityIDs.end(), comp.first) == entityIDs.end()) {
            entityIDs.push_back(comp.first);

            MyNode* IDRootNode = new MyNode { trueRootNode };
            IDRootNode->SetValue(std::to_string(comp.first));
//            IDNodes.insert(std::make_pair(comp.first, IDRootNode));
            nodeIDs.push_back(IDRootNode);
            nodeLocations.insert(std::make_pair(comp.first, nodeIDs.size()-1));

//            IDNodes[comp.first] = *IDRootNode;
            trueRootNode.AddChild(*IDRootNode);
        }
//        else {
//            MyNode internalRoot { IDNodes[comp.first] };
//
//        }
//        addDrawables(IDNodes[comp.first], comp.second);
//        MyNode* insertion = &IDNodes[comp.first];
//        addDrawables(*insertion, comp.second);
        addDrawables(*nodeIDs[nodeLocations[comp.first]], comp.second);
    }
    std::string test;
    test = "I get here, right?";
    /*
    for (auto const& comp : gravs)
    {   if (std::find(entityIDs.begin(), entityIDs.end(), comp.first) == entityIDs.end()) {
            entityIDs.push_back(comp.first);
        } else {

        }
    }
    for (auto const& comp : moves)
    {   if (std::find(entityIDs.begin(), entityIDs.end(), comp.first) == entityIDs.end()) {
            entityIDs.push_back(comp.first);
        } else {

        }
    }
    for (auto const& comp : positions)
    {   if (std::find(entityIDs.begin(), entityIDs.end(), comp.first) == entityIDs.end()) {
            entityIDs.push_back(comp.first);
        } else {

        }
    }
    for (auto const& comp : turns)
    {   if (std::find(entityIDs.begin(), entityIDs.end(), comp.first) == entityIDs.end()) {
            entityIDs.push_back(comp.first);
        } else{

        }
    } */
     // I feel like this isn't a GOOD solution but it is A (relatively clean) solution.


    // I'd need something filthy to distinguish between types? Or I'd implement that ISerializable suggestion...

    //for (int IDs : entityIDs)
    //{
    //   std::vector<std::vector<std::string>> toSave;
        //auto saveList = _entityManager->getComponentFromEntity(IDs);
    //}


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

    // Maybe change way of serializing?
    // vector[0] > component name
    // vector[1] > values separated by an unusual symbol?
    // Or maybe the names of each grouping instead?
    _writer.WriteXMLFile(myDoc, "LevelOne.xml");
    // cleaning of pointers to heap before exiting scope
    for (auto const& point : nodeIDs)
    {
        delete point;
    }
}

bool StorageSystem::loadWorld() {



    return false;
}
