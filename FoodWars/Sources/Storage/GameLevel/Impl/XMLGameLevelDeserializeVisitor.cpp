#include <string>
#include "../../../../Headers/Storage/GameLevel/Impl/XMLGameLevelDeserializeVisitor.h"
#include "../../../../Headers/StateMachine/Misc/GameLevel.h"

XMLGameLevelDeserializeVisitor::XMLGameLevelDeserializeVisitor(const MyDocument &document)
        : XMLDeserializationVisitor(document) {

}

void XMLGameLevelDeserializeVisitor::visit(const std::string &name, EntityManager &entityManager) {

}

void XMLGameLevelDeserializeVisitor::visit(const std::string &name, std::string &value) {
    XMLDeserializationVisitor::visit(name, value);
}

void XMLGameLevelDeserializeVisitor::visit(const std::string &name, int &value) {
    XMLDeserializationVisitor::visit(name, value);
}

void XMLGameLevelDeserializeVisitor::visit(const std::string &name, double &value) {
    XMLDeserializationVisitor::visit(name, value);
}

void XMLGameLevelDeserializeVisitor::visit(const std::string &name, bool &value) {
    XMLDeserializationVisitor::visit(name, value);
}

void XMLGameLevelDeserializeVisitor::visit(const std::string &name, SerializationReceiver &receiver) {
    XMLDeserializationVisitor::visit(name, receiver);
}

void XMLGameLevelDeserializeVisitor::visit(const std::string &name, std::vector<SerializationReceiver *> &receivers) {
    XMLDeserializationVisitor::visit(name, receivers);
}

void XMLGameLevelDeserializeVisitor::visit(const std::string &name, std::vector<SerializationReceiver *> &receivers,
                                           std::function<SerializationReceiver *()> createFunc) {
    XMLDeserializationVisitor::visit(name, receivers, createFunc);
}

void XMLGameLevelDeserializeVisitor::visit(GameLevel &value) {
    const MyNode *oldCurrent = _currentNode;
    //_currentNode = &_currentNode->AddChild(MyNode{name, _currentNode});
    value.accept(*this);
    _currentNode = oldCurrent;
}
