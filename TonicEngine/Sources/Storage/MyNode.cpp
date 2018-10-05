//
// Created by pietb on 01-Oct-18.
//

#include "../../Headers/Storage/MyNode.h"
MyNode::MyNode(std::string name, MyNode* parent)
        :_name(name), _parent(parent)
{

}


MyNode::~MyNode()
{
}

const string MyNode::GetName() const
{
    return _name;
}

const vector<MyNode> MyNode::GetChildren() const
{
    return _children;
}

const vector<Attribute> MyNode::GetAttributes() const
{
    return _attributes;
}

const string MyNode::GetValue() const
{
    return _value;
}

const int MyNode::GetIntValue() const
{
    return std::stoi(_value);
}

const MyNode* MyNode::GetParent() const
{
    return _parent;
}

const MyNode& MyNode::operator=(const MyNode & other)
{
    // TODO: insert return statement here
    _name = other.GetName();
    _children = other.GetChildren();
    _parent = const_cast<MyNode*>(other.GetParent());
    _attributes = other.GetAttributes();
    _value = other.GetValue();

    return *this;
}

MyNode& MyNode::AddChild(MyNode& child)
{
    //_children.push_back(child);
    _children.insert(_children.begin(), child);
    return child;
}

Attribute & MyNode::AddAttribute(Attribute & attribute)
{
    _attributes.push_back(attribute);
    return attribute;
}

MyNode* MyNode::FirstChildElement()
{
    if (_children.size() > 0)
    {
        return &_children[0];
    }
    else return nullptr;
}

const MyNode* MyNode::NextSiblingElement()
{
    int cur_count = 0;
    for (auto &sibl : GetParent()->GetChildren())
    {
        if (this == &sibl)
        {
            const MyNode* sibl_ptr{ &sibl.GetParent()->GetChildren()[cur_count++] };
            return sibl_ptr;
            //sibl_ptr =  &sibl.GetParent()->GetChildren()[cur_count++];
        }
        cur_count++;
    }

    return nullptr;
}

void MyNode::SetValue(string value)
{
    _value = value;
}

void MyNode::SetParent(MyNode& parent)
{
    _parent = &parent;
}

