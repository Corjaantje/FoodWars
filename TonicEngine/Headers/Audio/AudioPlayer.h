#ifndef PROJECT_SWA_AUDIOPLAYER_H
#define PROJECT_SWA_AUDIOPLAYER_H

#include <SDL2/SDL.h>

class AudioPlayer {
public:
    AudioPlayer();
    ~AudioPlayer();
    void playAudio(const char* path);
private:
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;
    SDL_AudioDeviceID deviceId;
    bool init();
};

#endif //PROJECT_SWA_AUDIOPLAYER_H