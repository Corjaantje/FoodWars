#ifndef PROJECT_SWA_XMLDESERIALIZATIONVISITOR_H
#define PROJECT_SWA_XMLDESERIALIZATIONVISITOR_H

#include "DeserializationVisitor.h"
#include "MyDocument.h"
#include "DeserializationFactory.h"

class XMLDeserializationVisitor : public DeserializationVisitor {
protected:
    const MyDocument *_document;
    const MyNode *_currentNode;
    DeserializationFactory _factory;
public:
    XMLDeserializationVisitor(const MyDocument &document, const DeserializationFactory &factory);

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

#endif //PROJECT_SWA_XMLDESERIALIZATIONVISITOR_H
