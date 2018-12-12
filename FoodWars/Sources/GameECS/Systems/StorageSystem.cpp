#include "../../../Headers/GameECS/Systems/StorageSystem.h"
// For checking # of files in directory

StorageSystem::StorageSystem() {
    _reader = new XMLReader();
    _writer = new XMLWriter();
}

StorageSystem::~StorageSystem() {
    delete _reader;
    delete _writer;
}