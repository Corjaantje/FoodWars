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

void StorageSystem::addDrawables(MyDocument& myDoc, std::map<int, std::shared_ptr<DrawableComponent>> toSave, vector<MyNode*>& existingIDNodes, std::map<int, int> &nodeLocations) {
    MyNode rootNode { myDoc.GetRoot() };
//    myNode.Get
    for (auto const& drawComp : toSave) {
        MyNode* IDNode = new MyNode { "id", nullptr };
        if (nodeLocations.count(drawComp.first))
        {
            IDNode = existingIDNodes[nodeLocations[drawComp.first]];
        } else {
            IDNode->SetParent(rootNode);
            IDNode->SetValue(std::to_string(drawComp.first));
        }
//        IDNode { std::to_string(drawComp.first), &rootNode };

        MyNode groupingNode { "drawablecomponent", IDNode };

        std::vector<std::string> filling = drawComp.second->serialize();

        if (filling[0] == "rectangle")
        {
            prepareRect(groupingNode, filling);
        }
        else if (filling[0] == "sprite")
        {
            prepareSprite(groupingNode, filling);
        } else if (filling[0] == "text")
        {
            prepareText(groupingNode, filling);
        } else
        {
            //TODO: throw an error?
        }
//        MyNode drawNode{filling[0], &groupingNode};
        /*
        // Gathering values of the position
        MyNode positionNode{filling[3], &groupingNode};

        MyNode xPos{"xpos", &positionNode};
        xPos.SetValue(filling[1]);
        MyNode yPos{"ypos", &positionNode};
        yPos.SetValue(filling[2]);

        positionNode.AddChild(yPos);
        positionNode.AddChild(xPos);

        // Gathering values of the "shape"
        MyNode shapeNode{"shape", &groupingNode};

        MyNode widthNode{"height", &shapeNode};
        widthNode.SetValue(filling[4]);
        MyNode heightNode{"width", &shapeNode};
        heightNode.SetValue(filling[5]);
        // MyNode colorNode { "color", &shape_node };
        // colorNode.SetValue(IDK MAN)

        shapeNode.AddChild(widthNode);
        shapeNode.AddChild(heightNode);
        //shape_node.AddChild(colorNode);



//        drawNode.AddChild(shapeNode);
//        drawNode.AddChild(positionNode);
//        groupingNode.AddChild(drawNode);
        groupingNode.AddChild(shapeNode);
        groupingNode.AddChild(positionNode);
        */
        IDNode->AddChild(groupingNode);

        myDoc.AddToRoot(*IDNode);
        rootNode.AddChild(*IDNode);

        if (!nodeLocations.count(drawComp.first)) {
            existingIDNodes.push_back(IDNode);
            nodeLocations.insert(std::make_pair(drawComp.first, existingIDNodes.size() - 1));
        }
    }
//    myDoc.AddToRoot()
//    myNode.AddChild(rootNode);

}

void StorageSystem::addGravity(MyDocument& myDoc, std::map<int, std::shared_ptr<GravityComponent>> toSave, vector<MyNode*> &existingIDNodes, std::map<int, int> &nodeLocations) {
    MyNode rootNode { myDoc.GetRoot() };
    for (auto const& gravComp : toSave) {
        MyNode* IDNode = new MyNode { "id", nullptr };
        if (nodeLocations.count(gravComp.first))
        {
            IDNode = existingIDNodes[nodeLocations[gravComp.first]];
        } else {
            IDNode->SetParent(rootNode);
            IDNode->SetValue(std::to_string(gravComp.first));
        }

        MyNode groupingNode { "gravitycomponent", IDNode };

        std::vector<std::string> filling = gravComp.second->serialize();

        MyNode gravNode{ "gravityapplied", &groupingNode};
        gravNode.SetValue(filling[0]);


        groupingNode.AddChild(gravNode);
        IDNode->AddChild(groupingNode);

        myDoc.AddToRoot(*IDNode);
        rootNode.AddChild(*IDNode);

        if (!nodeLocations.count(gravComp.first)) {
            existingIDNodes.push_back(IDNode);
            nodeLocations.insert(std::make_pair(gravComp.first, existingIDNodes.size() - 1));
        }
    }
}

void StorageSystem::addMove(MyDocument& myDoc, std::map<int, std::shared_ptr<MoveComponent>> toSave, vector<MyNode*> &existingIDNodes, std::map<int, int> &nodeLocations) {
    MyNode rootNode { myDoc.GetRoot() };
    for (auto const& moveComp : toSave) {
        MyNode* IDNode = new MyNode { "id", nullptr };
        if (nodeLocations.count(moveComp.first))
        {
            IDNode = existingIDNodes[nodeLocations[moveComp.first]];
        } else {
            IDNode->SetParent(rootNode);
            IDNode->SetValue(std::to_string(moveComp.first));
        }

        MyNode groupingNode { "movecomponent", IDNode };

        std::vector<std::string> filling = moveComp.second->serialize();

        MyNode xMoveNode{ "xvelo", &groupingNode};
        xMoveNode.SetValue(filling[0]);
        MyNode yMoveNode { "yvelo", &groupingNode};
        yMoveNode.SetValue(filling[1]);

        groupingNode.AddChild(xMoveNode);
        groupingNode.AddChild(yMoveNode);
        IDNode->AddChild(groupingNode);

        myDoc.AddToRoot(*IDNode);
        rootNode.AddChild(*IDNode);

        if (!nodeLocations.count(moveComp.first)) {
            existingIDNodes.push_back(IDNode);
            nodeLocations.insert(std::make_pair(moveComp.first, existingIDNodes.size() - 1));
        }
    }
}

void StorageSystem::addPosition(MyDocument& myDoc, std::map<int, std::shared_ptr<PositionComponent>> toSave, vector<MyNode*> &existingIDNodes, std::map<int, int> &nodeLocations) {
    MyNode rootNode { myDoc.GetRoot() };
    for (auto const& posComp : toSave) {
        MyNode* IDNode = new MyNode { "id", nullptr };
        if (nodeLocations.count(posComp.first))
        {
            IDNode = existingIDNodes[nodeLocations[posComp.first]];
        } else {
            IDNode->SetParent(rootNode);
            IDNode->SetValue(std::to_string(posComp.first));
        }

        MyNode groupingNode { "positioncomponent", IDNode };

        std::vector<std::string> filling = posComp.second->serialize();

        MyNode xNode{ "xpos", &groupingNode};
        xNode.SetValue(filling[0]);
        MyNode yNode { "ypos", &groupingNode};
        yNode.SetValue(filling[1]);

        groupingNode.AddChild(xNode);
        groupingNode.AddChild(yNode);
        IDNode->AddChild(groupingNode);

        myDoc.AddToRoot(*IDNode);
        rootNode.AddChild(*IDNode);

        if(!nodeLocations.count(posComp.first)) {
            existingIDNodes.push_back(IDNode);
            nodeLocations.insert(std::make_pair(posComp.first, existingIDNodes.size() - 1));
        }
    }
}

void StorageSystem::addTurns(MyDocument& myDoc, std::map<int, std::shared_ptr<TurnComponent>> toSave, vector<MyNode*> &existingIDNodes, std::map<int, int> &nodeLocations) {
    MyNode rootNode { myDoc.GetRoot() };
    for (auto const& turnComp : toSave) {
        MyNode* IDNode = new MyNode { "id", nullptr };
        if (nodeLocations.count(turnComp.first))
        {
            IDNode = existingIDNodes[nodeLocations[turnComp.first]];
        } else {
            IDNode->SetParent(rootNode);
            IDNode->SetValue(std::to_string(turnComp.first));
        }

        MyNode groupingNode { "turncomponent", IDNode };

        std::vector<std::string> filling = turnComp.second->serialize();

        MyNode energyNode{ "energy", &groupingNode};
        energyNode.SetValue(filling[0]);

        MyNode turnNode { "turn", &groupingNode};
        turnNode.SetValue(filling[1]);


        groupingNode.AddChild(energyNode);
        groupingNode.AddChild(turnNode);
        IDNode->AddChild(groupingNode);

        myDoc.AddToRoot(*IDNode);
        rootNode.AddChild(*IDNode);

        if (!nodeLocations.count(turnComp.first)) {
            existingIDNodes.push_back(IDNode);
            nodeLocations.insert(std::make_pair(turnComp.first, existingIDNodes.size() - 1));
        }
    }
}

void StorageSystem::prepareRect(MyNode& parentNode, std::vector<std::string> filling) {
    MyNode positionNode{filling[1], &parentNode};

    MyNode xPos{"xpos", &positionNode};
    xPos.SetValue(filling[2]);
    MyNode yPos{"ypos", &positionNode};
    yPos.SetValue(filling[3]);

    positionNode.AddChild(yPos);
    positionNode.AddChild(xPos);

    MyNode dimensionNode{filling[4], &parentNode};

    MyNode widthNode{"height", &dimensionNode};
    widthNode.SetValue(filling[5]);
    MyNode heightNode{"width", &dimensionNode};
    heightNode.SetValue(filling[6]);

    dimensionNode.AddChild(widthNode);
    dimensionNode.AddChild(heightNode);

    MyNode colorNode {filling[7], &parentNode};

    MyNode red {"red", &colorNode};
    red.SetValue(filling[8]);
    MyNode green {"green", &colorNode};
    green.SetValue(filling[9]);
    MyNode blue {"blue", &colorNode};
    blue.SetValue(filling[10]);
    MyNode alpha {"alpha", &colorNode};
    alpha.SetValue(filling[11]);

    colorNode.AddChild(red);
    colorNode.AddChild(green);
    colorNode.AddChild(blue);
    colorNode.AddChild(alpha);

    parentNode.AddChild(positionNode);
    parentNode.AddChild(dimensionNode);
    parentNode.AddChild(colorNode);
}

void StorageSystem::prepareSprite(MyNode& parentNode, std::vector<std::string> filling) {
    MyNode positionNode{filling[1], &parentNode};

    MyNode xPos{"xpos", &positionNode};
    xPos.SetValue(filling[2]);
    MyNode yPos{"ypos", &positionNode};
    yPos.SetValue(filling[3]);

    positionNode.AddChild(yPos);
    positionNode.AddChild(xPos);

    MyNode dimensionNode{filling[4], &parentNode};

    MyNode widthNode{"height", &dimensionNode};
    widthNode.SetValue(filling[5]);
    MyNode heightNode{"width", &dimensionNode};
    heightNode.SetValue(filling[6]);

    dimensionNode.AddChild(widthNode);
    dimensionNode.AddChild(heightNode);

    MyNode imageNode {filling[7], &parentNode};

    MyNode urlNode {"path", &imageNode};
    urlNode.SetValue(filling[8]);

    imageNode.AddChild(urlNode);

    parentNode.AddChild(positionNode);
    parentNode.AddChild(dimensionNode);
    parentNode.AddChild(imageNode);
}

void StorageSystem::prepareText(MyNode& parentNode, std::vector<std::string> filling) {
    MyNode positionNode{filling[1], &parentNode};

    MyNode xPos{"xpos", &positionNode};
    xPos.SetValue(filling[2]);
    MyNode yPos{"ypos", &positionNode};
    yPos.SetValue(filling[3]);

    positionNode.AddChild(yPos);
    positionNode.AddChild(xPos);

    MyNode dimensionNode{filling[4], &parentNode};

    MyNode widthNode{"height", &dimensionNode};
    widthNode.SetValue(filling[5]);
    MyNode heightNode{"width", &dimensionNode};
    heightNode.SetValue(filling[6]);

    dimensionNode.AddChild(widthNode);
    dimensionNode.AddChild(heightNode);

    MyNode colorNode {filling[7], &parentNode};

    MyNode red {"red", &colorNode};
    red.SetValue(filling[8]);
    MyNode green {"green", &colorNode};
    green.SetValue(filling[9]);
    MyNode blue {"blue", &colorNode};
    blue.SetValue(filling[10]);
    MyNode alpha {"alpha", &colorNode};
    alpha.SetValue(filling[11]);

    colorNode.AddChild(red);
    colorNode.AddChild(green);
    colorNode.AddChild(blue);
    colorNode.AddChild(alpha);

    MyNode textNode {"text", &parentNode};
    textNode.SetValue(filling[12]);

    parentNode.AddChild(positionNode);
    parentNode.AddChild(dimensionNode);
    parentNode.AddChild(colorNode);
}

void StorageSystem::assignRelevantEntityManager(std::shared_ptr<EntityManager> entityManager) {
    _entityManager = entityManager;
}

void StorageSystem::saveWorld() {
    int iTesting = 4;
    if (iTesting == 1) {
        WorldParser worldParser{};
        MyNode initialRootNode{"root", nullptr};
        MyDocument initialMyDoc{initialRootNode};

        // DrawableComponent
        // GravityComponent
        // MoveComponent
        // PositionComponent
        // TurnComponent
        initialMyDoc = worldParser.ParseDrawableComponents(initialMyDoc,
                                                           _entityManager->getAllEntitiesWithComponent<DrawableComponent>());

        std::string test1;
        test1 = "This code works, right?";
        _writer.WriteXMLFile(initialMyDoc, "LevelOne.xml");
    }

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
//    std::map<int, std::shared_ptr<DrawableComponent>> draws {_entityManager->getAllEntitiesWithComponent<DrawableComponent>()};
//    std::map<int, std::shared_ptr<GravityComponent>> gravs {_entityManager->getAllEntitiesWithComponent<GravityComponent>()};
//    std::map<int, std::shared_ptr<MoveComponent>> moves {_entityManager->getAllEntitiesWithComponent<MoveComponent>()};
//    std::map<int, std::shared_ptr<PositionComponent>> positions {_entityManager->getAllEntitiesWithComponent<PositionComponent>()};
//    std::map<int, std::shared_ptr<TurnComponent>> turns {_entityManager->getAllEntitiesWithComponent<TurnComponent>()};

    vector<int> entityIDs;
    std::map<int, int> nodeLocations;
    vector<MyNode*> nodeIDs;

    addDrawables(myDoc, _entityManager->getAllEntitiesWithComponent<DrawableComponent>(), nodeIDs, nodeLocations);
    addGravity(myDoc, _entityManager->getAllEntitiesWithComponent<GravityComponent>(), nodeIDs, nodeLocations);
    addMove(myDoc, _entityManager->getAllEntitiesWithComponent<MoveComponent>(), nodeIDs, nodeLocations);
    addPosition(myDoc, _entityManager->getAllEntitiesWithComponent<PositionComponent>(), nodeIDs, nodeLocations);
    addTurns(myDoc, _entityManager->getAllEntitiesWithComponent<TurnComponent>(), nodeIDs, nodeLocations);
    /*
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
    } */
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
//    myDoc.AddToRoot(trueRootNode);
    _writer.WriteXMLFile(myDoc, "LevelOne.xml");
    // cleaning of pointers to heap before exiting scope
    for (auto const& point : nodeIDs)
    {
        delete point;
    }
}

bool StorageSystem::loadWorld() {
//    MyDocument loadDoc = _reader.LoadFile("LevelOne.xml");
    MyNode rootNode = _reader.LoadFile("LevelOne.xml")->GetRoot();

    return false;
}
