#include "../../../../Headers/Storage/GameLevel/Impl/XMLGameLevelSerializeVisitor.h"
#include "../../../../Headers/StateMachine/Misc/GameLevel.h"

XMLGameLevelSerializeVisitor::XMLGameLevelSerializeVisitor(const std::string &rootName) : XMLSerializationVisitor(
        rootName) {

}

XMLGameLevelSerializeVisitor::~XMLGameLevelSerializeVisitor() = default;

void XMLGameLevelSerializeVisitor::visit(const std::string &name, const GameLevel &value) {
    MyNode *oldCurrent = _currentNode;
    _currentNode = &_currentNode->AddChild(MyNode{name, _currentNode});
    value.accept(*this);
    _currentNode = oldCurrent;
}

void XMLGameLevelSerializeVisitor::visit(const std::string &name, const EntityManager &entityManager) {
    MyNode *oldCurrent = _currentNode;
    addChildAndSetCurrentNode(name);
    for (const auto &entityIterator: entityManager.getAllEntitiesWithAllComponents()) {
        addChildAndSetCurrentNode("entity");
        for (const auto &componentIterator: entityIterator.second) {
            addChildAndSetCurrentNode(std::string{"c"} + typeid(*componentIterator).name());
            componentIterator->accept(static_cast<SerializationVisitor &>(*this));
            _currentNode = _currentNode->GetParent();
        }
        _currentNode = _currentNode->GetParent();
    }
    _currentNode = oldCurrent;
}

void XMLGameLevelSerializeVisitor::visit(const std::string &name, const std::string &value) {
    _currentNode->AddChild(MyNode{name, value, _currentNode});
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
