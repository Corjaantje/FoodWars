#include <string>
#include <iostream>
#include "../../Headers/Storage/XMLDeserializationVisitor.h"

XMLDeserializationVisitor::XMLDeserializationVisitor(const MyDocument &document, const DeserializationFactory &factory)
        : _document{&document},
          _currentNode{&document.GetRoot()},
          _factory{factory} {

}

void XMLDeserializationVisitor::visit(const std::string &name, std::string &value) {
    const auto child = _currentNode->GetChild(name);
    if (child)
        value = child->GetValue();
}

void XMLDeserializationVisitor::visit(const std::string &name, int &value) {
    const auto child = _currentNode->GetChild(name);
    if (child)
        value = child->GetIntValue();
}

void XMLDeserializationVisitor::visit(const std::string &name, double &value) {
    const auto child = _currentNode->GetChild(name);
    if (child)
        value = std::stod(child->GetValue());
}

void XMLDeserializationVisitor::visit(const std::string &name, bool &value) {
    const auto child = _currentNode->GetChild(name);
    if (child)
        value = child->GetValue() == "true";
}

void XMLDeserializationVisitor::visit(const std::string &name,
                                      SerializationReceiver &receiver) { //receiver must be already initialized and of the same type as in the XML
    const auto child = _currentNode->GetChild(name);
    if (child) {
        const MyNode *oldCurrent = _currentNode;
        _currentNode = child;
        receiver.accept(*this);
        _currentNode = oldCurrent;
    }
}

void XMLDeserializationVisitor::visit(const std::string &name, std::vector<SerializationReceiver *> &receivers) {
    const MyNode *oldCurrent = _currentNode;
    const MyNode *vectorNode = _currentNode->GetChild(name);
    if (vectorNode) {
        _currentNode = vectorNode;
        for (int i = 0; i < vectorNode->GetChildren().size(); i++) {
            const MyNode *child = vectorNode->GetChild(name + std::to_string(i));
            if (child) {
                const Attribute *typeAttribute = child->GetAttribute("typeName");
                if (typeAttribute) {
                    std::unique_ptr<SerializationReceiver> serializationReceiver = _factory.getSerializationReceiver(
                            typeAttribute->value);
                    if (serializationReceiver) {
                        SerializationReceiver *receiver = serializationReceiver.release();
                        _currentNode = child;
                        receiver->accept(*this);
                        receivers.push_back(receiver);
                    }
                }
            }
            _currentNode = vectorNode;
        }
    }
    _currentNode = oldCurrent;
}

void XMLDeserializationVisitor::visit(const std::string &name, std::vector<SerializationReceiver *> &receivers,
                                      std::function<SerializationReceiver *()> createFunc) {
    const MyNode *oldCurrent = _currentNode;
    const MyNode *vectorNode = _currentNode->GetChild(name);
    if (vectorNode) {
        _currentNode = vectorNode;
        for (int i = 0; i < vectorNode->GetChildren().size(); i++) {
            const MyNode *child = vectorNode->GetChild(name + std::to_string(i));
            if (child) {
                SerializationReceiver *receiver = createFunc();
                if (receiver) {
                    _currentNode = child;
                    receiver->accept(*this);
                }
            }
            _currentNode = vectorNode;
        }
    }
    _currentNode = oldCurrent;
}

void XMLDeserializationVisitor::visit(const std::string &name,
                                      std::vector<std::unique_ptr<SerializationReceiver>> &receivers) {
    const MyNode *oldCurrent = _currentNode;
    const MyNode *vectorNode = _currentNode->GetChild(name);
    if (vectorNode) {
        _currentNode = vectorNode;
        for (int i = 0; i < vectorNode->GetChildren().size(); i++) {
            const MyNode *child = vectorNode->GetChild(name + std::to_string(i));
            if (child) {
                const Attribute *typeAttribute = child->GetAttribute("typeName");
                if (typeAttribute) {
                    std::unique_ptr<SerializationReceiver> serializationReceiver = _factory.getSerializationReceiver(
                            typeAttribute->value);
                    if (serializationReceiver) {
                        _currentNode = child;
                        serializationReceiver->accept(*this);
                        receivers.push_back(std::move(serializationReceiver));
                    }
                }
            }
            _currentNode = vectorNode;
        }
    }
    _currentNode = oldCurrent;
}

void XMLDeserializationVisitor::visit(const std::string &name,
                                      SerializationReceiver *receiver) { //maybe make unique pointer?
    if (receiver) {
        receiver->accept(*this);
        return;
    }
    const MyNode *child = _currentNode->GetChild(name);
    if (child && !child->GetAttributes().empty()) {
        const Attribute *typeAttribute = child->GetAttribute("typeName");
        if (typeAttribute) {
            std::unique_ptr<SerializationReceiver> serializationReceiver = _factory.getSerializationReceiver(
                    typeAttribute->value);
            if (serializationReceiver) {
                receiver = serializationReceiver.release();
                receiver->accept(*this);
            }
        }
    }
}