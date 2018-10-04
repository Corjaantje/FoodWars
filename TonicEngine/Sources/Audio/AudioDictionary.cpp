#include "../../Headers/Audio/AudioDictionary.h"

AudioDictionary::AudioDictionary() {
    AudioDictionary::init();
}

AudioDictionary::~AudioDictionary() {
    delete _audioMap;
}

// Returns audio path with given key
const char* AudioDictionary::getAudio(const char* audioName) {
    const char* result = _audioMap->find(audioName)->second.c_str();
    return result;
}

void AudioDictionary::init(){
    // Create a new std::map
    _audioMap = new std::map<std::string,std::string>();

    // Add sounds to the map
    _audioMap->insert(std::pair<std::string,std::string>("oof", "../FoodWars/Assets/Audio/oof.wav") );
    _audioMap->insert(std::pair<std::string,std::string>("background", "../FoodWars/Assets/Audio/wildwest.wav"));
}




