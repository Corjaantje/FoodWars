#include <cstring>
#include "../../Headers/Audio/AudioFacade.h"

AudioFacade::AudioFacade() : _backgroundMusic(""){
    AudioFacade::init();
    for(int i=0; i< 2; i++){
        this->increaseEffectVolume();
    }
    for(int i=0; i<2; i++){
        this->increaseMusicVolume();
    }
}

AudioFacade::~AudioFacade() {
    delete _audioPlayer;
    delete _audioMap;
}

void AudioFacade::init(){
    // Create a new map
    _audioMap = new std::map<std::string,std::string>();

    // Create a new AudioPlayer
    _audioPlayer = new AudioPlayer();
}

// Returns the sound effect volume
int AudioFacade::getEffectVolume(){
    return _effectPercentage;
}

// Returns the music volume
int AudioFacade::getMusicVolume(){
    return _musicPercentage;
}

// Plays Music
void AudioFacade::playMusic(const char* filename) {

    // Check if filename is empty or null
    if(std::string(filename).empty() || filename == nullptr){
        _audioPlayer->stopMusic();
        return;
    }
    // Check if song is already playing
    if (std::string(filename) == std::string(_backgroundMusic))
        return;

    // Get path with the filename
    const char *path = getAudio(filename);

    if(path == nullptr){
        _audioPlayer->stopMusic();
        return;
    }
    // Create music
    Mix_Music *music;
    music=Mix_LoadMUS(path);
    if(!music)
        _audioPlayer->stopMusic();

    // Play sound with the path
    _audioPlayer->playMusic(path, -1);
    _backgroundMusic = std::string(filename);
}

// Plays a sound effect
void AudioFacade::playEffect(const char* filename){
    // Get path with the filename
    const char* path = getAudio(filename);

    // Play sound with the path
    _audioPlayer->playEffect(path);
}

// Adds a sound to the audioList
void AudioFacade::addAudio(std::string key,std::string path){
    _audioMap->insert(std::pair<std::string,std::string>(key, path) );
}

// Returns audio path with given key
const char* AudioFacade::getAudio(const char* audioName) {
    const char* result = _audioMap->find(audioName)->second.c_str();
    if(result == _audioMap->end()->second.c_str())
        return nullptr;
    return result;
}

void AudioFacade::increaseEffectVolume() {
    if(_audioPlayer->getEffectVolume() > 128-13){
        _audioPlayer->setEffectVolume(128);
        _effectPercentage = 10;
    }
    else{
        _audioPlayer->setEffectVolume(_audioPlayer->getEffectVolume()+13);
        if(_effectPercentage < 10){
            _effectPercentage++;
        }
    }
}

void AudioFacade::decreaseEffectVolume() {
    if(_audioPlayer->getEffectVolume() < 13){
        _audioPlayer->setEffectVolume(0);
        _effectPercentage = 0;
    }
    else{
        _audioPlayer->setEffectVolume(_audioPlayer->getEffectVolume()-13);
        if(_effectPercentage > 0){
            _effectPercentage--;
        }
    }
}

void AudioFacade::increaseMusicVolume() {
    if(_audioPlayer->getMusicVolume() > 128-13){
        _audioPlayer->setMusicVolume(128);
        _musicPercentage = 10;
    }
    else{
        _audioPlayer->setMusicVolume(_audioPlayer->getMusicVolume()+13);
        if(_musicPercentage < 10){
            _musicPercentage++;
        }
    }
}

void AudioFacade::decreaseMusicVolume() {
    if(_audioPlayer->getMusicVolume() < 13){
        _audioPlayer->setMusicVolume(0);
        _musicPercentage = 0;
    }
    else{
        _audioPlayer->setMusicVolume(_audioPlayer->getMusicVolume()-13);
        if(_musicPercentage > 0){
            _musicPercentage--;
        }
    }
}