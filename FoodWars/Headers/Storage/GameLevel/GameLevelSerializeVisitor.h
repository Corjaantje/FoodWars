#ifndef PROJECT_SWA_GAMELEVELSERIALIZER_H
#define PROJECT_SWA_GAMELEVELSERIALIZER_H

#include "../../../../TonicEngine/Headers/Storage/XMLSerializationVisitor.h"

class GameLevel;

class EntityManager;

class GameLevelSerializeVisitor : public virtual SerializationVisitor {
public:
    virtual void visit(const std::string &name, const std::string &value) = 0;

    virtual void visit(const std::string &name, const int &value) = 0;

    virtual void visit(const std::string &name, const double &value) = 0;

    virtual void visit(const std::string &name, const bool &value) = 0;

    void visit(const std::string &name, SerializationReceiver &receiver) override = 0;

    void visit(const std::string &name, std::vector<SerializationReceiver *> &receivers) override = 0;

    virtual void visit(const std::string &name, const GameLevel &value) = 0;

    virtual void visit(const std::string &name, const EntityManager &value) = 0;
};

#endif //PROJECT_SWA_GAMELEVELSERIALIZER_H
