#include <ctime>
#include "../../Headers/Storage/ScoreStorage.h"
#include "../../../TonicEngine/Headers/Storage/XMLReader.h"
#include "../../../TonicEngine/Headers/Storage/DeserializationFactory.h"
#include "../../../TonicEngine/Headers/Storage/XMLDeserializationVisitor.h"
#include "../../../TonicEngine/Headers/Storage/XMLWriter.h"
#include "../../Headers/Storage/GameLevel/Impl/XMLGameLevelSerializeVisitor.h"
#include "../../../TonicEngine/Headers/Storage/FileManager.h"

ScoreStorage::ScoreStorage() {

}

ScoreStorage::~ScoreStorage() {

}

void ScoreStorage::saveScore(int score, std::string levelName) {
    std::vector<Highscore> _highscores;
    std::string levelIdentifier = levelName.substr(levelName.length()-5, levelName.length() - 25);
    bool levelExists = false;
    std::time_t now = std::time(nullptr);
    tm *ltm = localtime(&now);
    std::string today = std::to_string(1900 + ltm->tm_year) + "-" + std::to_string(1 + ltm->tm_mon) + "-" +
                        std::to_string(ltm->tm_mday)+" "+std::to_string(ltm->tm_hour)+":"+std::to_string(ltm->tm_min);


    XMLReader reader{};
    MyDocument document = reader.LoadFile(DEFAULT_SCOREPATH);
    DeserializationFactory factory{};
    factory.addType<Highscore>();
    XMLDeserializationVisitor deserializationVisitor{document, factory};
    std::vector<SerializationReceiver *> v;
    deserializationVisitor.visit("highscore", v);

    for (SerializationReceiver *receiver: v) {
        auto *highscore = dynamic_cast<Highscore *>(receiver);
        if (highscore) {
            if (std::to_string(highscore->getID()) == levelIdentifier){
                levelExists = true;
                if (highscore->getScore() >= score) return;
                highscore->setDate(today);
                highscore->setScore(score);
            }
            _highscores.push_back(*highscore);
        }
    }

    if (!levelExists)
    {
        Highscore newHigh = Highscore {score, today, std::stoi(levelIdentifier)};
        _highscores.push_back(newHigh);
    }

    XMLWriter xmlWriter{};
    XMLSerializationVisitor serializeVisitor{"root"};
    std::vector<SerializationReceiver*> toSave;
    for (auto &iterator : _highscores)
    {
        toSave.push_back(static_cast<SerializationReceiver*>(&iterator));

    }
    serializeVisitor.visit("highscore", toSave);
    std::string file = DEFAULT_SCOREPATH;
    xmlWriter.WriteXMLFile(serializeVisitor.getRootNode(), file);
}


