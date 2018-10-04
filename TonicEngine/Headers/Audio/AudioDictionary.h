#ifndef PROJECT_SWA_AUDIODICTIONARY_H
#define PROJECT_SWA_AUDIODICTIONARY_H

#include <map>
#include <string>

class AudioDictionary {
public:
    AudioDictionary();
    ~AudioDictionary();
    const char* getAudio(const char* audioName);
private:
    void init();
    std::map<std::string,std::string> *_audioMap = nullptr;
};


#endif //PROJECT_SWA_AUDIODICTIONARY_H
