#ifndef PROJECT_SWA_GAMELEVELDESERIALIZEVISITOR_H
#define PROJECT_SWA_GAMELEVELDESERIALIZEVISITOR_H

#include "../../../../TonicEngine/Headers/Storage/DeserializationVisitor.h"
#include "../../GameECS/Entities/EntityManager.h"

class GameLevel;

class GameLevelDeserializeVisitor : public virtual DeserializationVisitor {
public:
    void visit(const std::string &name, std::string &value) override = 0;

    void visit(const std::string &name, int &value) override = 0;

    void visit(const std::string &name, double &value) override = 0;

    void visit(const std::string &name, bool &value) override = 0;

    void visit(const std::string &name, SerializationReceiver &receiver) override = 0;

    void visit(const std::string &name, std::vector<SerializationReceiver *> &receivers) override = 0;

    void visit(const std::string &name, std::vector<SerializationReceiver *> &receivers,
               std::function<SerializationReceiver *()> createFunc) override = 0;

    virtual void visit(const std::string &name, EntityManager &entityManager) = 0;

    virtual void visit(GameLevel &value) = 0;
};

#endif //PROJECT_SWA_GAMELEVELDESERIALIZEVISITOR_H
