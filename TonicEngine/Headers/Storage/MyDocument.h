#ifndef PROJECT_SWA_MYDOCUMENT_H
#define PROJECT_SWA_MYDOCUMENT_H

#include "MyNode.h"
#include <memory>
#include <cstring>

class MyDocument {
public:
    explicit MyDocument(const MyNode &root);

    /*MyDocument(const MyDocument& other) {
        std::cout << "MyDocument(const MyDocument& other)" << std::endl;
        _root(other._root.get());
    }
    MyDocument(MyDocument&& other) noexcept {
        std::cout << "(MyDocument&& other)" << std::endl;
        _root = other._root;
        other._root = nullptr;
    }
    MyDocument& operator=(MyDocument&& other) noexcept {
        std::cout << "=(MyDocument&& other)" << std::endl;
        if(this != &other) {
            _root = other._root;
            other._root = nullptr;
        }
        return *this;
    }*/
    ~MyDocument();

    const MyNode &GetRoot() const;
    //void AddToRoot(MyNode addition);

private:
    const MyNode _root;
};


#endif //PROJECT_SWA_MYDOCUMENT_H
