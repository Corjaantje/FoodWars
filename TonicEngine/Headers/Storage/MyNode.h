//
// Created by pietb on 01-Oct-18.
//

#ifndef PROJECT_SWA_MYNODE_H
#define PROJECT_SWA_MYNODE_H

#include <vector>
#include <string>

using namespace std;
struct Attribute {
    string name;
    string value;
};

class MyNode {
public:
    MyNode(const string &name, MyNode *parent);

    MyNode(const string &name, const string &value, MyNode *parent);

    ~MyNode();

    const string &GetName() const;

    const vector<MyNode> &GetChildren() const;

    const vector<Attribute> &GetAttributes() const;

    const string &GetValue() const;

    const int GetIntValue() const;

    const MyNode *GetParent() const;

    MyNode *GetParent();

    //MyNode &AddChild(MyNode &child);
    MyNode &AddChild(MyNode child);

    Attribute &AddAttribute(Attribute &attribute);

    const MyNode *FirstChildElement() const;

    MyNode *FirstChildElement();

    const MyNode *NextSiblingElement() const;

    void SetValue(const string &value);

    void SetParent(MyNode &parent);

    MyNode &operator=(const MyNode &other);

private:
    string _name;
    vector<MyNode> _children;
    MyNode *_parent;
    vector<Attribute> _attributes;
    string _value;
};


#endif //PROJECT_SWA_MYNODE_H
