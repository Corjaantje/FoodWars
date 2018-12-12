#include <string>
#include "../../../../Headers/Storage/GameLevel/Impl/XMLGameLevelDeserializeVisitor.h"
#include "../../../../Headers/StateMachine/Misc/GameLevel.h"

XMLGameLevelDeserializeVisitor::XMLGameLevelDeserializeVisitor(const MyDocument &document,
                                                               const DeserializationFactory &factory)
        : XMLDeserializationVisitor(document, factory) {

}

void XMLGameLevelDeserializeVisitor::visit(const std::string &name, EntityManager &entityManager) {
    const MyNode *oldCurrent = _currentNode;
    const MyNode *entityManagerNode = _currentNode->GetChild(name);
    if (!entityManagerNode) return;
    for (const MyNode &entity: entityManagerNode->GetChildren()) {
        int entityId = entityManager.createEntity();
        for (const MyNode &component: entity.GetChildren()) {
            _currentNode = &component;
            std::unique_ptr<Component> compPtr{
                    dynamic_cast<Component *>(XMLDeserializationVisitor::getSerializationReceiverFromNode(
                            &component).release())};
            entityManager.addComponentToEntity(entityId, std::move(compPtr));
        }
    }
    _currentNode = oldCurrent;
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

void XMLGameLevelDeserializeVisitor::visit(const std::string &name, std::unique_ptr<SerializationReceiver> &receiver) {
    XMLDeserializationVisitor::visit(name, receiver);
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

void XMLGameLevelDeserializeVisitor::visit(const std::string &name, SerializationReceiver *receiver) {
    XMLDeserializationVisitor::visit(name, receiver);
}

void XMLGameLevelDeserializeVisitor::visit(const std::string &name,
                                           std::vector<std::unique_ptr<SerializationReceiver>> &receivers) {
    XMLDeserializationVisitor::visit(name, receivers);
}
