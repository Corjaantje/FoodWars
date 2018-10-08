#ifndef PROJECT_SWA_AUDIO_H
#define PROJECT_SWA_AUDIO_H

#include <SDL2/SDL.h>
#include "AudioDictionary.h"
#include "AudioPlayer.h"

class AudioFacade {
public:
    AudioFacade();
    ~AudioFacade();
    void play(const char* filename);
private:
    AudioDictionary *_audioDictionary = nullptr;
    AudioPlayer *_audioPlayer = nullptr;
    void init();
};

#endif //PROJECT_SWA_AUDIO_H
