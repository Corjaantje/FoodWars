//
// Created by pietb on 09-Oct-18.
//

#include "../../Headers/Storage/StorageFacade.h"

// TODO: Check if either filepath has no corresponding file to read?
// Requires the correct filepaths on initialization
StorageFacade::StorageFacade(std::string system, std::string user) {
    XMLDocument doc;
    doc.LoadFile(system.c_str());
    _systemFile = _reader.ReadXMLFile(doc);

    doc.LoadFile(user.c_str());
    _userFile = _reader.ReadXMLFile(doc);
}

StorageFacade::~StorageFacade() {

}

// Retrieve highscore
string StorageFacade::getHighscore(int level) {

    std::unique_ptr<MyDocument> highscoreFile = _reader.LoadFile("Assets/highscore.xml");
    /*if (highscoreFile != nullptr) {
        string score = highscoreFile->GetRoot().GetChildren()[level].GetChildren()[0].GetValue();

        if (score != "") {
            return score;
        }
    }*/
    return "0";
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

MyDocument StorageFacade::getSystemXML() const{
    return *_systemFile;
}

MyDocument StorageFacade::getUserXML() const{
    return *_userFile;
}
