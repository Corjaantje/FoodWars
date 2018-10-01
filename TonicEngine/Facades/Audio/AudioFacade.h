#ifndef PROJECT_SWA_AUDIO_H
#define PROJECT_SWA_AUDIO_H

#include <SDL2/SDL.h>

class AudioFacade {
public:
    ~AudioFacade();
    void load(const char* filename);
    void play();
private:
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;
    SDL_AudioDeviceID deviceId;
};

#endif //PROJECT_SWA_AUDIO_H
