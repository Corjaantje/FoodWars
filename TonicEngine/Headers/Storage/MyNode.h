#ifndef PROJECT_SWA_MYNODE_H
#define PROJECT_SWA_MYNODE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;
struct Attribute {
    string name;
    string value;
};

class MyNode {
public:
    explicit MyNode(const string &name);

    MyNode(const string &name, const string &value);

    /*MyNode(const MyNode& other) {
        std::cout << "MyNode&" << std::endl;
        _parent = other._parent;
        _children = other._children;
        _attributes = other._attributes;
        _value = other._value;
        _name = other._name;
        _childrenByTagName = other._childrenByTagName;
        //_parent->_childrenByTagName[_name] = this;
    }

    MyNode(MyNode&& other) noexcept {
        std::cout << "MyNode&&" << std::endl;
        _parent = other._parent;
        _children = other._children;
        _childrenByTagName = other._childrenByTagName;
        _value = other._value;
        _name = other._name;
        _attributes = other._attributes;
        _parent->_childrenByTagName[_name] = this;
        other._parent = nullptr;
    }*/

    ~MyNode();

    const string &GetName() const;

    const vector<MyNode> &GetChildren() const;

    const MyNode *GetChild(const string &tagName) const;

    const vector<Attribute> &GetAttributes() const;

    const string &GetValue() const;

    const int GetIntValue() const;

    //MyNode &AddChild(MyNode &child);
    MyNode &AddChild(MyNode child);

    Attribute &AddAttribute(Attribute &attribute);

    void SetValue(const string &value);

    MyNode &operator=(const MyNode &other);

private:
    string _name;
    vector<MyNode> _children;
    std::unordered_map<std::string, MyNode *> _childrenByTagName;
    //MyNode *_parent;
    vector<Attribute> _attributes;
    string _value;
};


#endif //PROJECT_SWA_MYNODE_H
