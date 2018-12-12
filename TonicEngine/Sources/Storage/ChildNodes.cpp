#include "../../Headers/Storage/ChildNodes.h"
#include "../../Headers/Storage/MyNode.h"

ChildNodes::ChildNodes(std::vector<std::unique_ptr<MyNode>> &children) : _childOwner{std::move(children)},
                                                                         _childrenByTagName{}, _children{} {
    for (const auto &owner : _childOwner) {
        _childrenByTagName[owner->GetName()] = owner.get();
        _children.push_back(owner.get());
    }
}

MyNode *ChildNodes::addChild(MyNode child) {
    auto *ptr = new MyNode{child};
    _childOwner.push_back(std::unique_ptr<MyNode>(ptr));
    _children.push_back(ptr);
    _childrenByTagName[child.GetName()] = ptr;
    return ptr;
}

const std::vector<MyNode *> ChildNodes::getChildren() const {
    return _children;
}

std::vector<MyNode *> ChildNodes::getChildren() {
    return _children;
}

const MyNode *ChildNodes::getChild(const std::string &tagName) const {
    const auto child = _childrenByTagName.find(tagName);
    if (child != _childrenByTagName.end())
        return child->second;
    return nullptr;
}
