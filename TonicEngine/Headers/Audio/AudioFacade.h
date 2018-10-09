#ifndef PROJECT_SWA_AUDIO_H
#define PROJECT_SWA_AUDIO_H

#include <SDL2/SDL.h>
#include "AudioPlayer.h"
#include <string>
#include <map>

class AudioFacade {
public:
    AudioFacade();
    ~AudioFacade();
    void play(const char* filename);
    void addAudio(const char* key,const char* path);
private:
    //AudioDictionary *_audioDictionary = nullptr;
    std::map<std::string, std::string> *_audioMap = nullptr;
    AudioPlayer *_audioPlayer = nullptr;
    void init();
    const char* getAudio(const char* audioName);
};

#endif //PROJECT_SWA_AUDIO_H
