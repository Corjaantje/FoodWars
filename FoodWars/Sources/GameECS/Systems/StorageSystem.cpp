#include "../../../Headers/GameECS/Systems/StorageSystem.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/ShapeRectangle.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/ShapeSprite.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/ShapeText.h"

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


        rootNode.AddChild(*IDNode);

//        if (IDNode->NextSiblingElement() == nullptr)
//        {
//            myDoc.AddToRoot(*IDNode);
//        }
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


        rootNode.AddChild(*IDNode);

//        if (IDNode->NextSiblingElement() == nullptr)
//        {
//            myDoc.AddToRoot(*IDNode);
//        }
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


        rootNode.AddChild(*IDNode);

//        if (IDNode->NextSiblingElement() == nullptr)
//        {
//            myDoc.AddToRoot(*IDNode);
//        }
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


        rootNode.AddChild(*IDNode);

//        if (IDNode->NextSiblingElement() == nullptr)
//        {
//            myDoc.AddToRoot(*IDNode);
//        }
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


        rootNode.AddChild(*IDNode);

//        if (IDNode->NextSiblingElement() == nullptr)
//        {
//            myDoc.AddToRoot(*IDNode);
//        }
        if (!nodeLocations.count(turnComp.first)) {
            existingIDNodes.push_back(IDNode);
            nodeLocations.insert(std::make_pair(turnComp.first, existingIDNodes.size() - 1));
        }
    }
}

void StorageSystem::prepareRect(MyNode& parentNode, std::vector<std::string> filling) {
    // To keep track of type
    MyNode identifierNode{filling[0], &parentNode};

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
    parentNode.AddChild(identifierNode);
}

void StorageSystem::prepareSprite(MyNode& parentNode, std::vector<std::string> filling) {
    // To keep track of type
    MyNode identifierNode{filling[0], &parentNode};

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
    parentNode.AddChild(identifierNode);
}

void StorageSystem::prepareText(MyNode& parentNode, std::vector<std::string> filling) {
    // To keep track of type
    MyNode identifierNode{filling[0], &parentNode};

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
    parentNode.AddChild(identifierNode);
}

void StorageSystem::parseSavedInstance(MyNode &rootNode, EntityManager& _entity) {
    MyNode rootChild { "id", &rootNode};
    std::map<int, int> identifier{};

    int totalIDcount = 0;
    for (auto const& piece : rootNode.GetChildren())
    {
        int savedID = piece.GetIntValue();
        if (!identifier.count(savedID)) {
            identifier[savedID] = _entity.createEntity();
        }
        int childrenProcessed = 0;
        while (childrenProcessed < piece.GetChildren().size())
        {
            MyNode componentNode = piece.GetChildren()[childrenProcessed];
//            recursiveCrawl(componentNode, _entity, savedID);
            if (componentNode.GetName() == "drawablecomponent"){
                parseDrawable(componentNode, _entity, identifier[savedID]);
            }
            else if (componentNode.GetName() == "gravitycomponent"){
                parseGravity(componentNode, _entity, identifier[savedID]);
            }
            else if (componentNode.GetName() == "movecomponent"){
                parseMove(componentNode, _entity, identifier[savedID]);
            }
            else if (componentNode.GetName() == "positioncomponent"){
                // Not useful right now, seeing as positioncomponent seems to be a part of drawablecomponent
                // Maybe as a indication of spawnpoint?
                parsePosition(componentNode, _entity, identifier[savedID]);
            }
            else if (componentNode.GetName() == "turncomponent"){
                parseTurn(componentNode, _entity, identifier[savedID]);
            }
            childrenProcessed++;
        }
        totalIDcount++;

//        recursiveCrawl(piece.GetChildren()[0], _entity, savedID);
        /*
        if (piece.GetName() == "drawablecomponent"){
            parseDrawable(piece, _entity, identifier[savedID]);
        }
        else if (piece.GetName() == "gravitycomponent"){
            parseGravity(piece, _entity, identifier[savedID]);
        }
        else if (piece.GetName() == "movecomponent"){
            parseMove(piece, _entity, identifier[savedID]);
        }
        else if (piece.GetName() == "positioncomponent"){
            // Not useful right now, seeing as positioncomponent seems to be a part of drawablecomponent
            // Maybe as a indication of spawnpoint?
            parsePosition(piece, _entity, identifier[savedID]);
        }
        else if (piece.GetName() == "turncomponent"){
            parseTurn(piece, _entity, identifier[savedID]);
        }
        // */
    }
    std::string questioning = "Am I even doing it right?";
    /*
    MyNode idNodes { "id", rootNode.FirstChildElement()};
    while (idNodes.NextSiblingElement() != nullptr)
    {
        int savedID = idNodes.GetIntValue();
        if (!identifier.count(savedID)){
            identifier[savedID] = _entity.createEntity();
        }

        int childrenProcessed = 0;
        while (childrenProcessed < idNodes.GetChildren().size())
        {
            MyNode componentNode = idNodes.GetChildren()[childrenProcessed];
            recursiveCrawl(componentNode, _entity, savedID);
        }
//        recursiveCrawl(*idNodes.FirstChildElement(), _entity, savedID);
    }
     // */
//    std::vector<Attribute> atat = rootChild.GetAttributes();
//    const XMLAttribute* xmlAt = rootChild.GetAttributes();
}

void StorageSystem::recursiveCrawl(MyNode& piece, EntityManager& _entity, int id){
    if (piece.NextSiblingElement() == nullptr)
    {
        return;
    }
    else
    {
        if (piece.GetName() == "drawablecomponent"){
            parseDrawable(piece, _entity, id);
        }
        else if (piece.GetName() == "gravitycomponent"){
            parseGravity(piece, _entity, id);
        }
        else if (piece.GetName() == "movecomponent"){
            parseMove(piece, _entity, id);
        }
        else if (piece.GetName() == "positioncomponent"){
            // Not useful right now, seeing as positioncomponent seems to be a part of drawablecomponent
            // Maybe as a indication of spawnpoint?
            parsePosition(piece, _entity, id);
        }
        else if (piece.GetName() == "turncomponent"){
            parseTurn(piece, _entity, id);
        }
//        recursiveCrawl(piece.NextSiblingElement(), _entity, id);
    }
}

void StorageSystem::parseDrawable(const MyNode& drawableNode, EntityManager& _entity, int identifier) {
    DrawableComponent *comp = new DrawableComponent();
    _entity.addComponentToEntity(identifier, comp);

    std::vector<MyNode> childNodes = drawableNode.GetChildren();
    if (childNodes[0].GetName() == "rectangle") {
        // Frankenstein's monster?
        comp->shape = std::make_unique<ShapeRectangle>(ShapeRectangle({
            childNodes[2].GetChildren()[0].GetIntValue(),
            childNodes[2].GetChildren()[1].GetIntValue(),
            childNodes[3].GetChildren()[0].GetIntValue(),
            childNodes[3].GetChildren()[1].GetIntValue(),
            Colour{childNodes[1].GetChildren()[3].GetIntValue(),
                   childNodes[1].GetChildren()[2].GetIntValue(),
                   childNodes[1].GetChildren()[1].GetIntValue(),
                   childNodes[1].GetChildren()[0].GetIntValue()}}));
    }
    else if (childNodes[0].GetName() == "sprite") {

        comp->shape = std::make_unique<ShapeSprite>(ShapeSprite(
                childNodes[2].GetChildren()[0].GetIntValue(),
                childNodes[2].GetChildren()[1].GetIntValue(),
                childNodes[3].GetChildren()[0].GetIntValue(),
                childNodes[3].GetChildren()[1].GetIntValue(),
                childNodes[1].GetChildren()[0].GetValue()
                ));
    }
    else if (childNodes[0].GetName() == "text") {
        // filling[1]:  color
        //  2           alpha value
        //  3           blue
        //  4           green
        //  5           red
        //
        //
        //
        //
        comp->shape = std::make_unique<ShapeText>(ShapeText(
                childNodes[0].GetChildren()[0].GetIntValue(),
                childNodes[0].GetChildren()[0].GetIntValue(),
                childNodes[0].GetChildren()[0].GetValue(),
                childNodes[0].GetChildren()[0].GetIntValue(),
                childNodes[0].GetChildren()[0].GetIntValue(),
                childNodes[0].GetChildren()[0].GetIntValue(),
                Colour{childNodes[0].GetChildren()[0].GetIntValue(),
                       childNodes[0].GetChildren()[0].GetIntValue(),
                       childNodes[0].GetChildren()[0].GetIntValue(),
                       childNodes[0].GetChildren()[0].GetIntValue()}
                ));
    }
}

void StorageSystem::parseGravity(const MyNode& gravityNode, EntityManager& _entity, int identifier) {
    GravityComponent *comp = new GravityComponent();
    _entity.addComponentToEntity(identifier, comp);

    std::vector<MyNode> childNodes = gravityNode.GetChildren();
    comp->gravityApplied = childNodes[0].GetIntValue();
}

void StorageSystem::parseMove(const MyNode& moveNode, EntityManager& _entity, int identifier) {
    MoveComponent *comp = new MoveComponent();
    _entity.addComponentToEntity(identifier, comp);

    std::vector<MyNode> childNodes = moveNode.GetChildren();
    comp->xVelocity = childNodes[1].GetIntValue();
    comp->yVelocity = childNodes[0].GetIntValue();
}

void StorageSystem::parsePosition(const MyNode& positionNode, EntityManager& _entity, int identifier) {
    /*
    PositionComponent *comp = new PositionComponent();
    _entity.addComponentToEntity(identifier, comp);

    std::vector<MyNode> childNodes = positionNode.GetChildren();
     */
        // Bit of a special case I guess? Position is stored under DrawableComponent.
}

void StorageSystem::parseTurn(const MyNode& turnNode, EntityManager& _entity, int identifier) {
    std::vector<MyNode> childNodes = turnNode.GetChildren();
    TurnComponent *comp = new TurnComponent(childNodes[1].GetIntValue(), childNodes[0].GetIntValue());
    _entity.addComponentToEntity(identifier, comp);


//    comp->switchTurn(childNodes[0].GetIntValue());
    // Should I cast it or not?
//    comp->switchTurn(static_cast<bool>(childNodes[0].GetIntValue()));
//    comp->setEnergy(childNodes[1].GetIntValue());
    std::string teststring = "Odd.";

}

// Public functions

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
//    DrawableComponent *comp = new DrawableComponent();
//    int newID = _entityManager->createEntity();
//    _entityManager->addComponentToEntity(newID, comp);
//    comp->shape = std::make_unique<ShapeText>(ShapeText(
//            100, //x
//            200, //y
//            "Whatsup",
//            12, //size
//            16, //width
//            32, //height
//            Colour{160,
//                   200,
//                   50,
//                   100}
//    ));

    addDrawables(myDoc, _entityManager->getAllEntitiesWithComponent<DrawableComponent>(), nodeIDs, nodeLocations);
    addGravity(myDoc, _entityManager->getAllEntitiesWithComponent<GravityComponent>(), nodeIDs, nodeLocations);
    addMove(myDoc, _entityManager->getAllEntitiesWithComponent<MoveComponent>(), nodeIDs, nodeLocations);
    addPosition(myDoc, _entityManager->getAllEntitiesWithComponent<PositionComponent>(), nodeIDs, nodeLocations);
    addTurns(myDoc, _entityManager->getAllEntitiesWithComponent<TurnComponent>(), nodeIDs, nodeLocations);
    for (auto const& point : nodeIDs)
    {
        myDoc.AddToRoot(*point);
    }
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
    std::string testName = "LevelOne.xml";
    _writer.WriteXMLFile(myDoc, testName);
    // cleaning of pointers to heap before exiting scope
    for (auto const& point : nodeIDs)
    {
        delete point;
    }
//    std::shared_ptr<EntityManager> enterTaining;
//    loadWorld(enterTaining, testName);
}

bool StorageSystem::loadWorld(std::shared_ptr<EntityManager> toFill, std::string filePath) {
//    MyDocument loadDoc = _reader.LoadFile("LevelOne.xml");
    std::unique_ptr<MyDocument> myDoc = _reader.LoadFile("./"+filePath);
    MyNode rootNode = myDoc->GetRoot();
    bool bSuccess = false;
    parseSavedInstance(rootNode, *toFill);


    return bSuccess;
}




