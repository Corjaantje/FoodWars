#include <iostream>
#include "../../Headers/Audio/AudioPlayer.h"



AudioPlayer::AudioPlayer() {
    AudioPlayer::init();
}

AudioPlayer::~AudioPlayer() {
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);

}

bool AudioPlayer::init() {
    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        std::cerr << "Failed to initialize SDL Audio.\n";
        return 0;
    }
}

void AudioPlayer::playAudio(const char *path) {
   // Load audio file
    SDL_LoadWAV(path, &wavSpec, &wavBuffer, &wavLength);

    // Get default audio device
    deviceId = SDL_OpenAudioDevice(nullptr, 0, &wavSpec, nullptr, 0);

    // Queue audio
    SDL_QueueAudio(deviceId, wavBuffer, wavLength);

    // Play audio
    SDL_PauseAudioDevice(deviceId, 0);
}

