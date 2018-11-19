#ifndef PROJECT_SWA_STORAGESYSTEM_H
#define PROJECT_SWA_STORAGESYSTEM_H

#include "../../../../TonicEngine/Headers/Storage/XMLReader.h"
#include "../../../../TonicEngine/Headers/Storage/XMLWriter.h"
#include "../../Storage/Parsers/WorldParser.h"
#include "../../../../TonicEngine/Headers/Storage/StorageFacade.h"

#include "../Components/GravityComponent.h"
#include "../Components/MoveComponent.h"
#include "../Components/TurnComponent.h"
#include "../Components/Collider/BoxCollider.h"

#include <algorithm>


class StorageSystem{//}; : public IBaseSystem {
private:
    XMLReader* _reader;
    XMLWriter* _writer;
//    StorageFacade _storageFacade;
//    std::shared_ptr<EntityManager> _entityManager;
    EntityManager* _entityManager;
    template <typename Comp> void addComponentTypeOf(std::string compName, std::map<int, MyNode> &components, MyNode &rootNode);
    // part of Saving
    void addDrawables(MyDocument& myDoc, std::map<int, std::shared_ptr<DrawableComponent>> toSave, vector<MyNode*> &existingIDNodes, std::map<int, int> &nodeLocations);
    void addGravity(MyDocument& myDoc, std::map<int, std::shared_ptr<GravityComponent>> toSave, vector<MyNode*> &existingIDNodes, std::map<int, int> &nodeLocations);
    void addMove(MyDocument& myDoc, std::map<int, std::shared_ptr<MoveComponent>> toSave, vector<MyNode*> &existingIDNodes, std::map<int, int> &nodeLocations);
    void addPosition(MyDocument& myDoc, std::map<int, std::shared_ptr<PositionComponent>> toSave, vector<MyNode*> &existingIDNodes, std::map<int, int> &nodeLocations);
    void addTurns(MyDocument& myDoc, std::map<int, std::shared_ptr<TurnComponent>> toSave, vector<MyNode*> &existingIDNodes, std::map<int, int> &nodeLocations);
    void addCollideables(MyDocument& myDoc, std::map<int, std::shared_ptr<BoxCollider>> toSave, vector<MyNode*> &existingIDNodes, std::map<int, int> &nodeLocations);
    void prepareRect(MyNode& parentNode, std::vector<std::string> filling);
    void prepareSprite(MyNode& parentNode, std::vector<std::string> filling);
    void prepareText(MyNode& parentNode, std::vector<std::string> filling);
    // part of loading
    void parseSavedInstance(MyNode& rootNode, EntityManager& _entity);
    void recursiveCrawl(MyNode& baseNode, EntityManager& _entity, int id);
    void parseDrawable(const MyNode& drawableNode, EntityManager& _entity, int identifier);
    void parseGravity(const MyNode& gravityNode, EntityManager& _entity, int identifier);
    void parseMove(const MyNode& moveNode, EntityManager& _entity, int identifier);
    void parsePosition(const MyNode& positionNode, EntityManager& _entity, int identifier);
    void parseTurn(const MyNode& turnNode, EntityManager& _entity, int identifier);
    void parseCollideables(const MyNode& collideNode, EntityManager& _entity, int identifier);

    int countFilesInDirectory(std::string dir);
public:
    StorageSystem();
    ~StorageSystem();

    void assignRelevantEntityManager(EntityManager& entityManager);
//    void assignRelevantEntityManager(std::shared_ptr<EntityManager> entityManager);
    void saveWorld();//std::string savePath);

    // Pass a string for identifying the world?
    bool loadWorld(EntityManager& toFill, std::string filePath);
};


#endif //PROJECT_SWA_STORAGESYSTEM_H
