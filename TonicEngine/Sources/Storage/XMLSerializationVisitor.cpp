#include <string>
#include "../../Headers/Storage/SerializationReceiver.h"
#include "../../Headers/Storage/XMLSerializationVisitor.h"

XMLSerializationVisitor::XMLSerializationVisitor(const std::string &rootName) : _rootNode(rootName, nullptr),
                                                                                _currentNode(&_rootNode) {

}

void XMLSerializationVisitor::visit(const std::string &name, std::string &value) {
    _currentNode->AddChild(MyNode{name, value, _currentNode});
}

void XMLSerializationVisitor::visit(const std::string &name, int &value) {
    string s = std::to_string(value);
    visit(name, s);
}

void XMLSerializationVisitor::visit(const std::string &name, double &value) {
    string s = std::to_string(value);
    visit(name, s);
}

void XMLSerializationVisitor::visit(const std::string &name, bool &value) {
    string s = std::to_string(value);
    visit(name, s);
}

void XMLSerializationVisitor::visit(const std::string &name, SerializationReceiver &receiver) {
    MyNode *oldCurrent = _currentNode;
    _currentNode = &_currentNode->AddChild(MyNode{name, _currentNode});
    receiver.accept(*this);
    _currentNode = oldCurrent;
}

void XMLSerializationVisitor::visit(const std::string &name, std::vector<SerializationReceiver *> &receivers) {
    for (SerializationReceiver *receiver: receivers) {
        receiver->accept(*this);
    }
}

MyNode &XMLSerializationVisitor::getRootNode() {
    return _rootNode;
}


MyNode *XMLSerializationVisitor::addChildAndSetCurrentNode(const std::string &name) {
    _currentNode = &_currentNode->AddChild(MyNode{name, _currentNode});
    return _currentNode;
}
