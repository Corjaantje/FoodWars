#include "../../Headers/Audio/AudioFacade.h"

AudioFacade::~AudioFacade() {
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
}

void AudioFacade::load(const char* filename){
    SDL_LoadWAV(filename, &wavSpec, &wavBuffer, &wavLength);
    deviceId = SDL_OpenAudioDevice(nullptr, 0, &wavSpec, nullptr, 0);
}

void AudioFacade::play(){
    SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);
}