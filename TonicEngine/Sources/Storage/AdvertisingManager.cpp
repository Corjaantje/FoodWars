#include "../../Headers/Storage/AdvertisingManager.h"

#include <dirent.h>
#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include <algorithm>

AdvertisingManager::AdvertisingManager() {
    initializeAdvertisements(std::string("./Assets/Sprites/Advertisements/"));
}
AdvertisingManager::~AdvertisingManager() = default;

//init ads
void AdvertisingManager::initializeAdvertisements(std::string dir_name)
{
    DIR *dir;
    struct dirent *entry;
    struct stat info;

    dir = opendir(dir_name.c_str());
    if(!dir){
        return;
    }
    while((entry = readdir(dir)) != nullptr){
        if(entry->d_name[0] != '.'){
            std::string path = std::string(dir_name) + "/" + std::string(entry->d_name);
            stat(path.c_str(),&info);
            if(S_ISDIR(info.st_mode)){
                this->initializeAdvertisements(path);
            }
            else{
                if(path.find(".png") != std::string::npos){
                    _advertisements.emplace_back(entry->d_name);
                }
            }

        }
    };
    closedir(dir);
}

//returns all available ads
std::vector<std::string> AdvertisingManager::getAdvertisements() const {
    return _advertisements;
}

//reads currentAd from file
std::string AdvertisingManager::getCurrentAd() const {
    if (_advertisements.empty()) return "";

    std::ifstream f("./Assets/Sprites/Advertisements/current.txt");
    std::string firstLine;

    if (f.good())
    {
        getline(f, firstLine);
    }
    f.close();

    //if current.txt is empty or the advertisement mentioned does not exist -> take the first ad (last one in the vector)
    if (firstLine.empty() || std::find(_advertisements.begin(), _advertisements.end(), firstLine) == _advertisements.end()) {
        return _advertisements.back();
    }
    return firstLine;
}

//writes currentAd to file
void AdvertisingManager::setCurrentAd(const std::string& file) const {
    std::ofstream o("./Assets/Sprites/Advertisements/current.txt");
    if (o.is_open())
    {
        o << file << std::endl;
    }
    o.close();
}