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
                for(const auto &file: this->getFiles(path, fileExtension)) {
                    result.push_back(file);
                }
            } else{
                if(path.find(fileExtension) != std::string::npos){
                    result.emplace_back(path);
                }
            }

        }
    }
    closedir(dir);
    return result;
}

std::vector<std::string> FileManager::readFileLines(const std::string &filePath) const {
    std::ifstream f(filePath);
    std::vector<std::string> lines;

    if (f.good()) {
        for( std::string line; getline( f, line ); ){
            lines.push_back(line);
        }
    }
    f.close();

    return lines;
}

void FileManager::writeFileContent(const std::string &filePath, const std::string &content) const {
    std::ofstream o(filePath);
    if (o.is_open())
    {
        o << content << std::endl;
    }
    o.close();
}