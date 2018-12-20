
#include "../../Headers/Storage/MyDocument.h"

MyDocument::MyDocument(const MyNode &root) : _root(root) {

}

MyDocument::~MyDocument() = default;

const MyNode &MyDocument::GetRoot() const {
    return _root;
}

/*
void MyDocument::AddToRoot(MyNode addition) {
    _root->AddChild(std::move(addition));
}*/
