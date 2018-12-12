#include <algorithm>
#include "../../Headers/Storage/MyNode.h"

MyNode::MyNode(const std::string &name) : _name(name), _attributes() {

}

MyNode::MyNode(const string &name, const string &value) : _name{name}, _value{value} {

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

MyNode &MyNode::operator=(const MyNode &other) {
    _name = other.GetName();
    _children = other._children;
    _childrenByTagName = other._childrenByTagName;
    _attributes = other.GetAttributes();
    _value = other.GetValue();
    return *this;
}

MyNode &MyNode::AddChild(MyNode child) {
    _children.push_back(child);
    _childrenByTagName[child.GetName()] = &_children.back();
    return _children.back();
}

/*MyNode &MyNode::AddChild(MyNode &child) {
    _children.insert(_children.begin(), child);
    return child;
}*/

Attribute &MyNode::AddAttribute(Attribute &attribute) {
    _attributes.push_back(attribute);
    return attribute;
}

Attribute &MyNode::AddAttribute(const std::string &name, const std::string &value) {
    _attributes.emplace_back(name, value);
    return _attributes.back();
}

void MyNode::SetValue(const string &value) {
    _value = value;
}

const MyNode *MyNode::GetChild(const string &tagName) const {
    /*const auto child = _childrenByTagName.find(tagName);
    if(child != _childrenByTagName.end())
        return child->second;
    return nullptr;*/
    const auto child = std::find_if(_children.begin(), _children.end(), [&tagName](const MyNode &child) {
        return child.GetName() == tagName;
    });
    if (child != _children.end())
        return &(*child);
    return nullptr;
}

const Attribute *MyNode::GetAttribute(const string &name) const {
    const auto attribute = std::find_if(_attributes.begin(), _attributes.end(), [&name](const Attribute &a) {
        return a.name == name;
    });
    if (attribute != _attributes.end())
        return &(*attribute);
    return nullptr;
}
