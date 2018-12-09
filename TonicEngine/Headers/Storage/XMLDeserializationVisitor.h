#ifndef PROJECT_SWA_XMLDESERIALIZATIONVISITOR_H
#define PROJECT_SWA_XMLDESERIALIZATIONVISITOR_H

#include "DeserializationVisitor.h"

class XMLDeserializationVisitor : public DeserializationVisitor {
public:
    XMLDeserializationVisitor() = default;

    void visit(const std::string &name, std::string &value) override;

    void visit(const std::string &name, int &value) override;

    void visit(const std::string &name, double &value) override;

    void visit(const std::string &name, bool &value) override;

    void visit(const std::string &name, SerializationReceiver &receiver) override;

    void visit(const std::string &name, std::vector<SerializationReceiver *> &receivers) override;

    void visit(const std::string &name, std::vector<SerializationReceiver *> &receivers,
               std::function<SerializationReceiver *()> createFunc) override;

};

#endif //PROJECT_SWA_XMLDESERIALIZATIONVISITOR_H
