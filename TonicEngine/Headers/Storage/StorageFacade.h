//
// Created by pietb on 09-Oct-18.
//

#ifndef PROJECT_SWA_STORAGEFACADE_H
#define PROJECT_SWA_STORAGEFACADE_H

#include <string>

#include "XMLReader.h"
#include "XMLWriter.h"
#include "../../Facades/IFacade.h"

class StorageFacade : public IFacade {
private:
    std::unique_ptr<MyDocument> _systemFile;
    std::unique_ptr<MyDocument> _userFile;

    XMLReader _reader;
    XMLWriter _writer;
public:
    StorageFacade(std::string system, std::string user);
    ~StorageFacade();

    bool setTarget(std::string target);

    // Manually testing while factories haven't been implemented yet.
    MyDocument getSystemXML() const;
    MyDocument getUserXML() const;

    string getHighscore(int level);

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
