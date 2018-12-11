#ifndef PROJECT_SWA_XMLGAMELEVELDESERIALIZEVISITOR_H
#define PROJECT_SWA_XMLGAMELEVELDESERIALIZEVISITOR_H

#include "../GameLevelDeserializeVisitor.h"
#include "../../../../../TonicEngine/Headers/Storage/XMLDeserializationVisitor.h"

class XMLGameLevelDeserializeVisitor : public virtual GameLevelDeserializeVisitor, public XMLDeserializationVisitor {
public:
    explicit XMLGameLevelDeserializeVisitor(const MyDocument &document);

    void visit(const std::string &name, EntityManager &entityManager) override;

    void visit(GameLevel &value) override;

    void visit(const std::string &name, std::string &value) override;

    void visit(const std::string &name, int &value) override;

    void visit(const std::string &name, double &value) override;

    void visit(const std::string &name, bool &value) override;

    void visit(const std::string &name, SerializationReceiver &receiver) override;

    void visit(const std::string &name, std::vector<SerializationReceiver *> &receivers) override;

    void visit(const std::string &name, std::vector<SerializationReceiver *> &receivers,
               std::function<SerializationReceiver *()> createFunc) override;
};

#endif //PROJECT_SWA_XMLGAMELEVELDESERIALIZEVISITOR_H
