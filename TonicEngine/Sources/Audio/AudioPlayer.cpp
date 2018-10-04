#include <iostream>
#include "../../Headers/Audio/AudioPlayer.h"

AudioPlayer::AudioPlayer() {
    AudioPlayer::init();
}

AudioPlayer::~AudioPlayer() {
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);

}

void AudioPlayer::playAudio(const char *path) {
    SDL_LoadWAV(path, &wavSpec, &wavBuffer, &wavLength);
    deviceId = SDL_OpenAudioDevice(nullptr, 0, &wavSpec, nullptr, 0);

    // Play the audio
    SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);
}

bool AudioPlayer::init() {
    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        std::cerr << "Failed to initialize SDL Audio.\n";
        return 0;
    }
}