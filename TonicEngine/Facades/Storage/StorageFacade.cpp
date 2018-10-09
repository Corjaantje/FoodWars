//
// Created by pietb on 09-Oct-18.
//

#include "../../Headers/Storage/StorageFacade.h"

StorageFacade::StorageFacade() {

}

StorageFacade::~StorageFacade() {

}

// To allow switching between desired files.
// Returns true if the desired file has been found. Prepares readableFile if true;
bool StorageFacade::setTarget(std::string target) {
    /* XMLDocument doc;
    if (doc.LoadFile(target.c_str()))
    {
        //_readableFile = _reader.ReadXMLFile(doc);
        return true;
    }*/
    return false;
}

// Reading
void StorageFacade::getAudioComponents() {

}

void StorageFacade::getLevels() {

}

void StorageFacade::getTextures() {

}

void StorageFacade::getSavedGameData() {

}

void StorageFacade::getSavedUserData() {

}

void StorageFacade::getWeapons() {

}

// Writing
void StorageFacade::saveCustomLevels() {

}

void StorageFacade::saveGameData() {

}

void StorageFacade::saveUserData() {

}

void StorageFacade::saveCustomWeapons() {

}
