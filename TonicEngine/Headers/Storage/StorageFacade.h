//
// Created by pietb on 09-Oct-18.
//

#ifndef PROJECT_SWA_STORAGEFACADE_H
#define PROJECT_SWA_STORAGEFACADE_H

#include <string>

#include "XMLReader.h"
#include "XMLWriter.h"

class StorageFacade {
private:

    XMLReader _reader;
    XMLWriter _writer;
public:
    StorageFacade();
    ~StorageFacade();

    bool setTarget(std::string target);

    // Placeholders for loading. Will end up using factories to return usable objects.
    void getAudioComponents();
    void getLevels();
    void getTextures();
    void getSavedGameData();
    void getSavedUserData();
    void getWeapons();


    // Placeholders for writing.
    void saveCustomLevels();
    void saveGameData();
    void saveUserData();
    void saveCustomWeapons();
};

#endif //PROJECT_SWA_STORAGEFACADE_H
