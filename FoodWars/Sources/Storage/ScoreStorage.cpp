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

void ScoreStorage::loadScore() {
    XMLReader reader{};
    MyDocument document = reader.LoadFile("./Assets/highscore.xml");
    DeserializationFactory factory{};
    factory.addType<Highscore>();
    XMLDeserializationVisitor deserializationVisitor{document, factory};
    std::vector<SerializationReceiver *> v;
    deserializationVisitor.visit("highscore", v);
    int i = 0;
    for (SerializationReceiver *receiver: v) {
        Highscore *highscore = dynamic_cast<Highscore *>(receiver);
//        if (highscore)
            _highscores.emplace_back(highscore);
//        delete highscore;
    }
}
void ScoreStorage::saveScore(int score, std::string levelName) {
    _highscores.clear();
    loadScore();

    std::string levelIdentifier = levelName.substr(levelName.length()-5, levelName.length() - 25);
    for (auto &iterator : _highscores)
    {
        if (std::to_string(iterator->getID()) == levelName)
        {
            if (iterator->getScore() <= score)
                return;
            std::time_t now = std::time(nullptr);
            tm *ltm = localtime(&now);
            std::string today = std::to_string(1900 + ltm->tm_year) + "-" + std::to_string(1 + ltm->tm_mon) + "-" +
                                std::to_string(ltm->tm_mday)+" "+std::to_string(ltm->tm_hour)+":"+std::to_string(ltm->tm_min);
            iterator->setDate(today);

            iterator->setScore(score);
        }
    }

    XMLWriter xmlWriter{};
    XMLSerializationVisitor serializeVisitor{"Highscore"};
    std::vector<SerializationReceiver*> toSave;
    for (auto &iterator : _highscores)
    {
        toSave.push_back(static_cast<SerializationReceiver*>(iterator));

    }
    serializeVisitor.visit("Highscore", toSave);
    std::string file = DEFAULT_XMLPATH;
    xmlWriter.WriteXMLFile(serializeVisitor.getRootNode(), file);
}


