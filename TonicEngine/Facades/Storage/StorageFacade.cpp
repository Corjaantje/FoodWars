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
    _systemFile = _reader.ReadXMLFile(doc);

    doc.LoadFile(user.c_str());
    _userFile = _reader.ReadXMLFile(doc);
}

StorageFacade::~StorageFacade() {

}

// Retrieve highscore
string StorageFacade::getHighscore(int level) {

    std::unique_ptr<MyDocument> highscoreFile = _reader.LoadFile("Assets/Highscore.xml");
    if (highscoreFile != nullptr) {
        string score = highscoreFile->GetRoot().GetChildren()[level].GetChildren()[0].GetValue();

        if (score != "") {
            return score;
        }
    }
    return "0";
}

std::vector<std::vector<std::string>> StorageFacade::getHighscoresAndLevels() {
    std::unique_ptr<MyDocument> highscoreFile = _reader.LoadFile("Assets/Highscore.xml");
    std::vector<std::vector<std::string>> vLevels;

    for (auto const& lvl : highscoreFile->GetRoot().GetChildren())
    {
        std::vector<std::string> toFill {lvl.GetName(),
                                         (lvl.GetChildren()[0].GetValue() != "") ? lvl.GetChildren()[0].GetValue() : 0};
        vLevels.push_back(toFill);
    }

    return vLevels;
}

void StorageFacade::saveHighscore(int score, std::string level) {
//    (_lastPlayedLevelPath.substr(5, _lastPlayedLevelPath.length() - 9));
//    "./Assets/Levels/Level3.xml"
//    From start to needed: 16
//    Needed length: 6
//    Extra: 4
//    Total length: 26
    std::string levelIdentifier = level.substr(level.length()-5, level.length() - 25);
    XMLWriter scoreSaver;// = XMLWriter();
//    MyNode rootNode {"highscore", nullptr};
//    MyDocument doc {rootNode};

    std::unique_ptr<MyDocument> highDoc = _reader.LoadFile("Assets/Highscore.xml");
    MyNode rootNode = highDoc->GetRoot();
    std::vector<MyNode *> savedNodes;
    int nodeId = -1;
    int previouslyScored = false;

    MyNode saveRoot {"highscore", nullptr};
    for (auto const &scored : rootNode.GetChildren())
    {
        MyNode* tempNode = new MyNode {"level", &saveRoot};
        tempNode->SetValue(scored.GetValue());

        MyNode tempScore {"score", tempNode};
        tempScore.SetValue(scored.GetChildren()[0].GetValue());

        MyNode tempDate {"date", tempNode};
        tempDate.SetValue(scored.GetChildren()[1].GetValue());

        tempNode->AddChild(tempDate);
        tempNode->AddChild(tempScore);
        savedNodes.push_back(tempNode);

        if (scored.GetValue() == levelIdentifier)
        {
            previouslyScored = true;
//            MyNode levelScore = scored.GetChildren()[0];//.SetValue(std::to_string(score));
//            levelScore.SetValue(std::to_string(score));
        }
    }
    if (!previouslyScored)
    {
//        MyNode newScore {"level", &rootNode};
        MyNode newScore {"level", &saveRoot};
        newScore.SetValue(levelIdentifier.substr(5, levelIdentifier.length()-5));

        MyNode newHigh {"score", &newScore};
        newHigh.SetValue(std::to_string(score));

        MyNode onDate {"date", &newScore};
        std::time_t now = std::time(0);
        tm *ltm = localtime(&now);
        std::string today = std::to_string(1970+ltm->tm_yday)+"-"+std::to_string(1+ltm->tm_mon)+"-"+std::to_string(ltm->tm_mday);
        onDate.SetValue(today);

        newScore.AddChild(onDate);
        newScore.AddChild(newHigh);

        rootNode.AddChild(newScore);
    }
    else
    {
//        MyNode levelNode {rootNode.GetChildren()[nodeId]};
//        MyNode scoreNode {levelNode.GetChildren()[0]};
//        scoreNode.SetValue(std::to_string(score));
        MyNode* levelNode = savedNodes[nodeId];
        MyNode scoreNode {levelNode->GetChildren()[0]};
        scoreNode.SetValue(std::to_string(score));
    }
//    for (auto const& node : savedNodes)
//    {
//        saveRoot.AddChild(*node);
//
//    }
//    for (std::vector<MyNode *>::reverse_iterator i = savedNodes.rbegin(); i != savedNodes.rend(); ++i)
//    for (auto i = savedNodes.rbegin(); i != savedNodes.rend(); ++i)
//    {
//        saveRoot.AddChild(*savedNodes[i]);
//    }
    for (int i = savedNodes.size()-1; i > 0; i--)
    {
        saveRoot.AddChild(*savedNodes[i]);
    }

    MyDocument saveDoc{saveRoot};
//    _writer.WriteXMLFile(*highDoc, "Assets/Highscore.xml");
    _writer.WriteXMLFile(saveDoc, "Assets/Highscore.xml");

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
