#include "../../Headers/Audio/AudioFacade.h"
#include "../../Headers/Audio/AudioDictionary.h"

AudioFacade::AudioFacade() {
    AudioFacade::init();
}

AudioFacade::~AudioFacade() {
    delete _audioPlayer;
    delete _audioDictionary;
}

void AudioFacade::init(){
    _audioDictionary = new AudioDictionary();
    _audioPlayer = new AudioPlayer();
}

// Plays a sound
void AudioFacade::play(const char* filename){
    // Get path with the filename
    const char* path = _audioDictionary->getAudio(filename);

    // Play sound with the path
    _audioPlayer->playAudio(path);
}