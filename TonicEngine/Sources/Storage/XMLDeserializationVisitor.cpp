#include <string>
#include <iostream>
#include "../../Headers/Storage/XMLDeserializationVisitor.h"
#include "../../Headers/Storage/SerializationReceiver.h"

XMLDeserializationVisitor::XMLDeserializationVisitor(const MyDocument &document) : _document{&document},
                                                                                   _currentNode{&document.GetRoot()} {

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

void XMLDeserializationVisitor::visit(const std::string &name, SerializationReceiver &receiver) {
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
            _currentNode = vectorNode->GetChild("elem" + std::to_string(
                    i)); //todo: hardcoded names to a factory, or each SerializationReceiver must have a name function
            //receiver.accept(*this);
            std::cerr << "This is not working!!" << std::endl;
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
            _currentNode = vectorNode->GetChild("elem" + std::to_string(
                    i)); //todo: hardcoded names to a factory, or each SerializationReceiver must have a name function
            createFunc()->accept(*this);// warning: maybe need to add to the vector
            _currentNode = vectorNode;
        }
    }
    _currentNode = oldCurrent;
}
