#include "../../../../Headers/Storage/GameLevel/Impl/XMLGameLevelSerializeVisitor.h"
#include "../../../../Headers/StateMachine/Misc/GameLevel.h"

XMLGameLevelSerializeVisitor::XMLGameLevelSerializeVisitor(const std::string &rootName) : XMLSerializationVisitor(
        rootName) {

}

XMLGameLevelSerializeVisitor::~XMLGameLevelSerializeVisitor() = default;

void XMLGameLevelSerializeVisitor::visit(const std::string &name, const EntityManager &entityManager) {
    MyNode *oldCurrent = _currentNode;
    MyNode *entityManagerNode = addChildAndSetCurrentNode(name);
    SerializationVisitor &serializationVisitor = static_cast<SerializationVisitor &>(*this);
    for (const auto &entityIterator: entityManager.getAllEntitiesWithAllComponents()) {
        MyNode *entityNode = addChildAndSetCurrentNode("entity");
        for (const Component *componentIterator: entityIterator.second) {
            visit("component", (SerializationReceiver &) *componentIterator);
        }
        _currentNode = entityManagerNode;
    }
    _currentNode = oldCurrent;
}

void XMLGameLevelSerializeVisitor::visit(const std::string &name, const std::string &value) {
    _currentNode->AddChild(MyNode{name, value});
}

void XMLGameLevelSerializeVisitor::visit(const std::string &name, const int &value) {
    string s = std::to_string(value);
    visit(name, s);
}

void XMLGameLevelSerializeVisitor::visit(const std::string &name, const double &value) {
    string s = std::to_string(value);
    visit(name, s);
}

void XMLGameLevelSerializeVisitor::visit(const std::string &name, const bool &value) {
    string s = std::to_string(value);
    visit(name, s);
}

void XMLGameLevelSerializeVisitor::visit(const std::string &name, SerializationReceiver &receiver) {
    XMLSerializationVisitor::visit(name, receiver);
}

void XMLGameLevelSerializeVisitor::visit(const std::string &name, std::vector<SerializationReceiver *> &receivers) {
    XMLSerializationVisitor::visit(name, receivers);
}

void XMLGameLevelSerializeVisitor::visit(const GameLevel &value) {
    MyNode *oldCurrent = _currentNode;
    //_currentNode = &_currentNode->AddChild(MyNode{name, _currentNode});
    value.accept(*this);
    _currentNode = oldCurrent;
}
