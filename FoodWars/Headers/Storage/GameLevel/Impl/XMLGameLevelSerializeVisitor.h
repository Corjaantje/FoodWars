#ifndef PROJECT_SWA_XMLGAMELEVELSERIALIZEVISITOR_H
#define PROJECT_SWA_XMLGAMELEVELSERIALIZEVISITOR_H

#include "../GameLevelSerializeVisitor.h"
#include "../../../../../TonicEngine/Headers/Storage/XMLSerializationVisitor.h"

class XMLGameLevelSerializeVisitor : public virtual GameLevelSerializeVisitor, public XMLSerializationVisitor {
public:
    explicit XMLGameLevelSerializeVisitor(const std::string &rootName);

    ~XMLGameLevelSerializeVisitor();

    void visit(const GameLevel &value) override;

    void visit(const std::string &name, const EntityManager &value) override;

    void visit(const std::string &name, const std::string &value) override;

    void visit(const std::string &name, const int &value) override;

    void visit(const std::string &name, const double &value) override;

    void visit(const std::string &name, const bool &value) override;

    void visit(const std::string &name, SerializationReceiver &receiver) final;

    void visit(const std::string &name, std::vector<SerializationReceiver *> &receivers) final;
};

#endif //PROJECT_SWA_XMLGAMELEVELSERIALIZEVISITOR_H
