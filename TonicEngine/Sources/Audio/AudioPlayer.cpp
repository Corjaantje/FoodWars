#include <iostream>
#include "../../Headers/Audio/AudioPlayer.h"



AudioPlayer::AudioPlayer() {
    AudioPlayer::init();
}

AudioPlayer::~AudioPlayer() {
    Mix_Quit();
}

bool AudioPlayer::init() {
    // Initialize SDL_Audio
    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        std::cerr << "Failed to initialize SDL Audio.\n";
        return false;
    }

    // Open mixer
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        std::cerr << "Error: " << Mix_GetError() << std::endl;

    // Allocate audio channels
    Mix_AllocateChannels(16);
}

// Sets the music volume
void AudioPlayer::setMusicVolume(int volume) {
    if(volume > 0 && volume < 128)
        Mix_VolumeMusic(volume);
}

// Sets the sound effect volume
void AudioPlayer::setEffectVolume(int volume) {
    if(volume > 0 && volume < 128)
    Mix_Volume(-1, volume);
}

// Plays Music
void AudioPlayer::playMusic(const char *path, int amountOfLoops) {

    // Load music
    Mix_Music *audio = Mix_LoadMUS(path);

    // Play music
    Mix_PlayMusic(audio, amountOfLoops);

    // Cleanup
    path = nullptr;
    audio = nullptr;
}

void AudioPlayer::playEffect(int channelNumber, const char *path, int amountOfLoops) {

    // Load sound effect
    Mix_Chunk *audio = Mix_LoadWAV(path);

    // Play the sound effect
    if(Mix_PlayChannel(channelNumber, audio, amountOfLoops) == -1)
    {
        // Show error if assigned channel isn't available
        std::cerr << "Audio channel not available.\n";
    }

    // Cleanup
    path = nullptr;
    audio = nullptr;
}

