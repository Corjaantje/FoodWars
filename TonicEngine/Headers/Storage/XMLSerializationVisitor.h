#ifndef PROJECT_SWA_XMLSERIALIZATIONVISITOR_H
#define PROJECT_SWA_XMLSERIALIZATIONVISITOR_H

#include "SerializationVisitor.h"
#include "MyNode.h"

class XMLSerializationVisitor : public virtual SerializationVisitor {
protected:
    MyNode _rootNode;
    MyNode *_currentNode;

    MyNode *addChildAndSetCurrentNode(const std::string &name);

public:
    explicit XMLSerializationVisitor(const std::string &rootName);

    void visit(const std::string &name, std::string &value) override;

    void visit(const std::string &name, int &value) override;

    void visit(const std::string &name, double &value) override;

    void visit(const std::string &name, bool &value) override;

    void visit(const std::string &name, SerializationReceiver &receiver) override;

    void visit(const std::string &name, SerializationReceiver *receiver) override;

    void visit(const std::string &name, std::vector<SerializationReceiver *> &receivers) override;

    MyNode &getRootNode();
};

#endif //PROJECT_SWA_XMLSERIALIZATIONVISITOR_H
