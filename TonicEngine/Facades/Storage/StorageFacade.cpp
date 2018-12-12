//
// Created by pietb on 09-Oct-18.
//

#include <ctime>
#include "../../Headers/Storage/StorageFacade.h"

// TODO: Check if either filepath has no corresponding file to read?
// Requires the correct filepaths on initialization
StorageFacade::StorageFacade(std::string system, std::string user) {
    XMLDocument doc;
    doc.LoadFile(system.c_str());
    /* _systemFile = _reader.ReadXMLFile(doc);

     doc.LoadFile(user.c_str());
     _userFile = _reader.ReadXMLFile(doc);*/
}

StorageFacade::~StorageFacade() = default;

// Retrieve highscore
string StorageFacade::getHighscore(int level) {

    std::unique_ptr<MyDocument> highscoreFile = _reader.LoadFile2("Assets/Highscore.xml");
    if (highscoreFile != nullptr) {
        string score = highscoreFile->GetRoot().GetChildren()[level].GetChildren()[0].GetValue();

        if (!score.empty()) {
            return score;
        }
    }
    return "0";
}

std::vector<std::vector<std::string>> StorageFacade::loadHighscoresForLevels(const DeserializationFactory &factory) {
    std::unique_ptr<MyDocument> highscoreFile = _reader.LoadFile2("Assets/Highscore.xml");
    std::vector<std::vector<std::string>> vLevels;
    for (auto const& iterator : highscoreFile->GetRoot().GetChildren())
    {
        std::vector<std::string> toFill {iterator.GetName(),
                                         (!iterator.GetChildren()[0].GetValue().empty()) ? iterator.GetChildren()[0].GetValue() : nullptr,
                                         (!iterator.GetChildren()[1].GetValue().empty()) ? iterator.GetChildren()[1].GetValue() : nullptr};
        vLevels.emplace_back(toFill);
    }

    return vLevels;
}

void StorageFacade::saveHighscore(int score, std::string level) {
//    "./Assets/Levels/Level3.xml"
//    From start to needed: 16
//    Needed length: 6
//    Extra: 4
//    Total length: 26
    std::string levelIdentifier = level.substr(level.length()-5, level.length() - 25);

    std::unique_ptr<MyDocument> highDoc = _reader.LoadFile2("Assets/Highscore.xml");
    MyNode rootNode = highDoc->GetRoot();
    std::vector<MyNode *> savedNodes{};
    int nodeId = -1;
    int previouslyScored = false;

    MyNode saveRoot {"root", nullptr};
    MyDocument saveDoc {saveRoot};
    for (auto const &iterator : rootNode.GetChildren())
    {
        if (iterator.GetValue().substr(0, iterator.GetValue().length()-8) == levelIdentifier)
        {
            previouslyScored = true;
            MyNode *tempNode = new MyNode{"level"};
            tempNode->SetValue(levelIdentifier);

            MyNode tempScore{"score"};
            if (score > iterator.GetChildren()[0].GetIntValue())
            {
                tempScore.SetValue(std::to_string(score));
            } else
            {
                tempScore.SetValue(iterator.GetChildren()[0].GetValue());
            }

            MyNode tempDate{"date"};
            std::time_t now = std::time(nullptr);
            tm *ltm = localtime(&now);
            std::string today = std::to_string(1900 + ltm->tm_year) + "-" + std::to_string(1 + ltm->tm_mon) + "-" +
                                std::to_string(ltm->tm_mday)+" "+std::to_string(ltm->tm_hour)+":"+std::to_string(ltm->tm_min);
            tempDate.SetValue(today);

            tempNode->AddChild(tempDate);
            tempNode->AddChild(tempScore);
            savedNodes.push_back(tempNode);
        } else
        {
            MyNode *tempNode = new MyNode{"level"};
            tempNode->SetValue(iterator.GetValue().substr(0, iterator.GetValue().length()-8));

            MyNode tempScore{"score"};
            tempScore.SetValue(iterator.GetChildren()[0].GetValue());

            MyNode tempDate{"date"};
            tempDate.SetValue(iterator.GetChildren()[1].GetValue());

            tempNode->AddChild(tempDate);
            tempNode->AddChild(tempScore);
            savedNodes.push_back(tempNode);
        }
    }
    if (!previouslyScored)
    {
        MyNode *newScore = new MyNode{"level"};
        newScore->SetValue(levelIdentifier);

        MyNode newHigh{"score"};
        newHigh.SetValue(std::to_string(score));

        MyNode onDate{"date"};
        std::time_t now = std::time(nullptr);
        tm *ltm = localtime(&now);
        std::string today = std::to_string(1900+ltm->tm_year)+"-"+std::to_string(1+ltm->tm_mon)+"-"+std::to_string(ltm->tm_mday)+" "+std::to_string(ltm->tm_hour)+":"+std::to_string(ltm->tm_min);
        onDate.SetValue(today);

        newScore->AddChild(onDate);
        newScore->AddChild(newHigh);
        savedNodes.push_back(newScore);
    }
    /*for (int i = savedNodes.size()-1; i >= 0; i--)
    {
        saveDoc.AddToRoot(*savedNodes[i]);
    }*/
    auto* written = new XMLWriter();
    written->WriteXMLFile(saveDoc, "./Assets/Highscore.xml");
    delete written;
    for (int i = savedNodes.size()-1; i >= 0; i--)
    {
        delete savedNodes[i];
    }

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
