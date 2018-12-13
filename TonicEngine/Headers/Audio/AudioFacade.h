#ifndef PROJECT_SWA_AUDIO_H
#define PROJECT_SWA_AUDIO_H

#include "AudioPlayer.h"
#include "../../Facades/IFacade.h"
#include <string>
#include <cstring>
#include <map>

class AudioFacade : public IFacade {
public:
    AudioFacade();
    ~AudioFacade();
    int getEffectVolume();
    int getMusicVolume();
    void increaseEffectVolume();
    void decreaseEffectVolume();
    void increaseMusicVolume();
    void decreaseMusicVolume();
    void playMusic(const char* filename);
    void playEffect(const char* filename);
    void addAudio(std::string key,std::string path);
private:
    std::map<std::string, std::string> *_audioMap = nullptr;
    AudioPlayer* _audioPlayer = nullptr;
    std::string _backgroundMusic;
    int _effectPercentage = 0;
    int _musicPercentage = 0;
    void init();
    const char* getAudio(const char* audioName);
};

#endif //PROJECT_SWA_AUDIO_H
