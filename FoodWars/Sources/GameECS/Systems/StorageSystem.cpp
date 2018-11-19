#include "../../../Headers/GameECS/Systems/StorageSystem.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/ShapeRectangle.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/ShapeSprite.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/ShapeText.h"
// For checking # of files in directory
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

StorageSystem::StorageSystem() {

}

StorageSystem::~StorageSystem() {

}

// May be worth keeping? Would make for a nicer implementation than the current one. Do not know how to make it work.
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
    for (auto const& drawComp : toSave) {
        MyNode* IDNode = new MyNode { "id", nullptr };
        if (nodeLocations.count(drawComp.first))
        {
            IDNode = existingIDNodes[nodeLocations[drawComp.first]];
        } else {
            IDNode->SetParent(rootNode);
            IDNode->SetValue(std::to_string(drawComp.first));
        }
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

        IDNode->AddChild(groupingNode);

        rootNode.AddChild(*IDNode);


        if (!nodeLocations.count(drawComp.first)) {
            existingIDNodes.push_back(IDNode);
            nodeLocations.insert(std::make_pair(drawComp.first, existingIDNodes.size() - 1));
        }
    }

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
    }
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
        // Bit of a special case I guess? Position is stored under DrawableComponent.
}

void StorageSystem::parseTurn(const MyNode& turnNode, EntityManager& _entity, int identifier) {
    std::vector<MyNode> childNodes = turnNode.GetChildren();
    TurnComponent *comp = new TurnComponent(childNodes[1].GetIntValue(), childNodes[0].GetIntValue());
    _entity.addComponentToEntity(identifier, comp);

}

int StorageSystem::countFilesInDirectory(char* dir) {
    DIR *dp;
    int filesInDir = 0;
    struct dirent *ep;
    dp = opendir(dir);

    if (dp != NULL)
    {
        while (ep == readdir (dp))
        {
            filesInDir++;
        }
        (void) closedir(dp);
    }
    return filesInDir;
}
// Public functions

void StorageSystem::assignRelevantEntityManager(std::shared_ptr<EntityManager> entityManager) {
    _entityManager = entityManager;
}

void StorageSystem::saveWorld(){//std::string savePath) {
    MyNode trueRootNode {"root", nullptr};
    MyDocument myDoc { trueRootNode };

    std::map<int, int> nodeLocations;
    vector<MyNode*> nodeIDs;

    addDrawables(myDoc, _entityManager->getAllEntitiesWithComponent<DrawableComponent>(), nodeIDs, nodeLocations);
    addGravity(myDoc, _entityManager->getAllEntitiesWithComponent<GravityComponent>(), nodeIDs, nodeLocations);
    addMove(myDoc, _entityManager->getAllEntitiesWithComponent<MoveComponent>(), nodeIDs, nodeLocations);
    addPosition(myDoc, _entityManager->getAllEntitiesWithComponent<PositionComponent>(), nodeIDs, nodeLocations);
    addTurns(myDoc, _entityManager->getAllEntitiesWithComponent<TurnComponent>(), nodeIDs, nodeLocations);
    for (auto const& point : nodeIDs)
    {
        myDoc.AddToRoot(*point);
    }


//    Get number of files in the Levels directory


    std::string savingName = "Level"+to_string(countFilesInDirectory(const_cast<char *>("./Levels/")));

    _writer.WriteXMLFile(myDoc, savingName);

    for (auto const& point : nodeIDs)
    {
        delete point;
    }
}

bool StorageSystem::loadWorld(std::shared_ptr<EntityManager> toFill, std::string filePath) {
    std::unique_ptr<MyDocument> myDoc = _reader.LoadFile("./"+filePath);
    MyNode rootNode = myDoc->GetRoot();
    bool bSuccess = false;
    parseSavedInstance(rootNode, *toFill);


    return bSuccess;
}






