#ifndef PROJECT_SWA_CHILDNODES_H
#define PROJECT_SWA_CHILDNODES_H

#include <vector>
#include <memory>
#include <unordered_map>

class MyNode;

class ChildNodes {
private:
    std::vector<std::unique_ptr<MyNode>> _childOwner;
    std::vector<MyNode *> _children;
    std::unordered_map<std::string, MyNode *> _childrenByTagName;
public:
    ChildNodes() = default;

    explicit ChildNodes(std::vector<std::unique_ptr<MyNode>> &children);

    MyNode *addChild(MyNode child);

    const std::vector<MyNode *> getChildren() const;

    std::vector<MyNode *> getChildren();

    const MyNode *getChild(const std::string &tagName) const;

};

#endif //PROJECT_SWA_CHILDNODES_H
