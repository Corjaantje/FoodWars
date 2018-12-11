#ifndef PROJECT_SWA_XMLGAMELEVELDESERIALIZEVISITOR_H
#define PROJECT_SWA_XMLGAMELEVELDESERIALIZEVISITOR_H

#include "../GameLevelDeserializeVisitor.h"
#include "../../../../../TonicEngine/Headers/Storage/XMLDeserializationVisitor.h"

class XMLGameLevelDeserializeVisitor : public virtual GameLevelDeserializeVisitor, public XMLDeserializationVisitor {
public:
    XMLGameLevelDeserializeVisitor(const MyDocument &document, const DeserializationFactory &factory);

    void visit(const std::string &name, EntityManager &entityManager) override;

    void visit(GameLevel &value) override;

    void visit(const std::string &name, std::string &value) override;

    void visit(const std::string &name, int &value) override;

    void visit(const std::string &name, double &value) override;

    void visit(const std::string &name, bool &value) override;

    void visit(const std::string &name, SerializationReceiver &receiver) override;

    void visit(const std::string &name, SerializationReceiver *receiver) override;

    void visit(const std::string &name, std::vector<SerializationReceiver *> &receivers) override;

    void visit(const std::string &name, std::vector<SerializationReceiver *> &receivers,
               std::function<SerializationReceiver *()> createFunc) override;

    void visit(const std::string &name, std::vector<std::unique_ptr<SerializationReceiver>> &receivers) override;

};

#endif //PROJECT_SWA_XMLGAMELEVELDESERIALIZEVISITOR_H
