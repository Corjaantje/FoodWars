#include <iostream>
#include "../../Headers/Audio/AudioPlayer.h"



AudioPlayer::AudioPlayer() : _effectVolume{10}, _musicVolume{5}{
    AudioPlayer::init();
    Mix_VolumeMusic(_musicVolume);
    Mix_Volume(-1, _effectVolume);
}

AudioPlayer::~AudioPlayer() {
    while(Mix_Init(0))
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

// Returns the sound effect volume
int AudioPlayer::getEffectVolume(){
    return _effectVolume;
}

// Returns the music volume
int AudioPlayer::getMusicVolume(){
    return _musicVolume;
}

// Sets the music volume
void AudioPlayer::setMusicVolume(int volume) {
    if(volume > -1 && volume < 129)
    {
        _musicVolume = volume;
        Mix_VolumeMusic(volume);
    }
}

// Sets the sound effect volume
void AudioPlayer::setEffectVolume(int volume) {
    if(volume > -1 && volume < 129)
    {
        _effectVolume = volume;
        Mix_Volume(-1, volume);
    }
}

// Plays Music
void AudioPlayer::playMusic(const char *path, int amountOfLoops) {
    // Load music
    Mix_Music *audio = Mix_LoadMUS(path);

    // Play music
    Mix_PlayMusic(audio, amountOfLoops);
    Mix_ResumeMusic();
}

void AudioPlayer::stopMusic(){
    Mix_PauseMusic();
}


void AudioPlayer::playEffect(const char *path) {

    // Load sound effect
    Mix_Chunk *audio = Mix_LoadWAV(path);

    // Play the sound effect
    if(Mix_PlayChannel(-1, audio, 0) == -1)
    {
        // Show error if assigned channel isn't available
        std::cerr << "Audio channel not available.\n";
    }
}

