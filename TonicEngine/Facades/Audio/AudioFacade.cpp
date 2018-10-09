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

    // Create a new AudioPlayer
    _audioPlayer = new AudioPlayer();
}

// Sets the music volume
void AudioFacade::setMusicVolume(int volume) {
    _audioPlayer->setMusicVolume(volume);
}

// Sets the sound effect volume
void AudioFacade::setEffectVolume(int volume) {
    _audioPlayer->setEffectVolume(volume);
}

// Plays Music
void AudioFacade::playMusic(const char* filename, int amountOfLoops){
    // Get path with the filename
    const char* path = getAudio(filename);

    // Play sound with the path
    _audioPlayer->playMusic(path, amountOfLoops);
}

// Plays a sound effect
void AudioFacade::playEffect(const char* filename){
    // Get path with the filename
    const char* path = getAudio(filename);

    // Play sound with the path
    _audioPlayer->playEffect(path);
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