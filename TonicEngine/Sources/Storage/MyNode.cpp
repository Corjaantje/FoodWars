//
// Created by pietb on 01-Oct-18.
//

#include "../../Headers/Storage/MyNode.h"

MyNode::MyNode(const std::string &name, MyNode *parent)
        : _name(name), _parent(parent), _attributes() {

}

MyNode::MyNode(const string &name, const string &value, MyNode *parent) : _name{name}, _value{value}, _parent{parent} {

}

MyNode::~MyNode() = default;

const string &MyNode::GetName() const {
    return _name;
}

const vector<MyNode> &MyNode::GetChildren() const {
    return _children;
}

const vector<Attribute> &MyNode::GetAttributes() const {
    return _attributes;
}

const string &MyNode::GetValue() const {
    return _value;
}

const int MyNode::GetIntValue() const {
    return std::stoi(_value);
}

const MyNode *MyNode::GetParent() const {
    return _parent;
}

MyNode &MyNode::operator=(const MyNode &other) {
    _name = other.GetName();
    _children = other.GetChildren();
    _parent = const_cast<MyNode *>(other.GetParent());
    _attributes = other.GetAttributes();
    _value = other.GetValue();
    return *this;
}

MyNode &MyNode::AddChild(MyNode child) {
    _children.insert(_children.begin(), child);
    return _children.at(0);
}

/*MyNode &MyNode::AddChild(MyNode &child) {
    _children.insert(_children.begin(), child);
    return child;
}*/

Attribute &MyNode::AddAttribute(Attribute &attribute) {
    _attributes.push_back(attribute);
    return attribute;
}

const MyNode *MyNode::FirstChildElement() const {
    if (!_children.empty()) {
        return &_children.at(0);
    } else return nullptr;
}

MyNode *MyNode::FirstChildElement() {
    if (!_children.empty()) {
        return &_children.at(0);
    } else return nullptr;
}

const MyNode *MyNode::NextSiblingElement() const {
    int cur_count = 0;
    for (auto &sibl : GetParent()->GetChildren()) {
        if (this == &sibl) {
            return &sibl.GetParent()->GetChildren()[cur_count++];
            //sibl_ptr =  &sibl.GetParent()->GetChildren()[cur_count++];
        }
        cur_count++;
    }

    return nullptr;
}

void MyNode::SetValue(const string &value) {
    _value = value;
}

void MyNode::SetParent(MyNode &parent) {
    _parent = &parent;
}

MyNode *MyNode::GetParent() {
    return _parent;
}

