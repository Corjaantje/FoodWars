#include "../../Headers/Storage/FileManager.h"

#include <dirent.h>
#include <iostream>
#include <sys/stat.h>
#include <fstream>

FileManager::FileManager() = default;
FileManager::~FileManager() = default;

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

std::string FileManager::readFileContent(const std::string &filePath) const {
    std::ifstream f(filePath);
    std::string firstLine;

    if (f.good())
    {
        getline(f, firstLine);
    }
    f.close();

    return firstLine;
}

void FileManager::writeFileContent(const std::string &filePath, const std::string &content) const {
    std::ofstream o(filePath);
    if (o.is_open())
    {
        o << content << std::endl;
    }
    o.close();
}