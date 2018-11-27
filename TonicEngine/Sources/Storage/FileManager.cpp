#include "../../Headers/Storage/FileManager.h"

#include <dirent.h>
#include <iostream>
#include <sys/stat.h>
FileManager::FileManager() = default;
FileManager::~FileManager() = default;

std::vector<std::string> FileManager::getFilesWithoutExtension(const std::string &filePath,
                                                               const std::string &fileExtension) const {
    DIR *dir;
    struct dirent *entry;
    struct stat info{};
    std::vector<std::string> result;

    dir = opendir(filePath.c_str());
    if(!dir){
        return result;
    }
    while((entry = readdir(dir)) != nullptr){
        if(entry->d_name[0] != '.'){
            std::string path = std::string(filePath) + "/" + std::string(entry->d_name);
            stat(path.c_str(),&info);
            if(S_ISDIR(info.st_mode)){
                this->getFiles(path, fileExtension);
            }
            else{
                if(path.find(fileExtension) != std::string::npos){
                    std::string file = entry->d_name;
                    std::string raw = file.substr(0, file.find_last_of('.'));
                    result.emplace_back(raw);
                }
            }

        }
    }
    closedir(dir);
}
std::vector<std::string> FileManager::getFiles(const std::string &filePath, const std::string &fileExtension) const {
    DIR *dir;
    struct dirent *entry;
    struct stat info{};
    std::vector<std::string> result;

    dir = opendir(filePath.c_str());
    if(!dir){
        return result;
    }
    while((entry = readdir(dir)) != nullptr){
        if(entry->d_name[0] != '.'){
            std::string path = std::string(filePath) + "/" + std::string(entry->d_name);
            stat(path.c_str(),&info);
            if(S_ISDIR(info.st_mode)){
                this->getFiles(path, fileExtension);
            }
            else{
                if(path.find(fileExtension) != std::string::npos){
                    result.emplace_back(entry->d_name);
                }
            }

        }
    }
    closedir(dir);
}