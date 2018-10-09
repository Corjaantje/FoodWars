#include "../../Headers/Audio/AudioFacade.h"

AudioFacade::AudioFacade() {
    AudioFacade::init();
}

AudioFacade::~AudioFacade() {
    delete _audioPlayer;
    delete _audioMap;
}

void AudioFacade::init(){
    // Create a new map
    _audioMap = new std::map<std::string,std::string>();
    //_audioDictionary = new AudioDictionary();
    _audioPlayer = new AudioPlayer();
}

// Plays a sound
void AudioFacade::play(const char* filename){
    // Get path with the filename
    const char* path = getAudio(filename);

    // Play sound with the path
    _audioPlayer->playAudio(path);
}

// Adds a sound to the audioList
void AudioFacade::addAudio(const char* key,const char* path){
    _audioMap->insert(std::pair<std::string,std::string>(key, path) );
}

// Returns audio path with given key
const char* AudioFacade::getAudio(const char* audioName) {
    const char* result = _audioMap->find(audioName)->second.c_str();
    return result;
}