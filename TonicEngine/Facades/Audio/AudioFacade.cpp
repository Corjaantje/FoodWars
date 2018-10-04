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
    // Create AudioDictionary
    _audioDictionary = new AudioDictionary();
    _audioPlayer = new AudioPlayer();
}

void AudioFacade::play(const char* filename){
    // Get the audio path
    const char* path = _audioDictionary->getAudio(filename);
    _audioPlayer->playAudio(path);
}