#include "../../Headers/Storage/FileManager.h"

#include <dirent.h>
#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include <algorithm>

FileManager::FileManager() = default;
FileManager::~FileManager() = default;

std::vector<std::string> FileManager::getFiles(const std::string &filePath,
                                  const std::vector<std::string>& fileExtension,
                                  bool includeExtension,
                                  bool includeSubFolders) const {
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
            if(S_ISDIR(info.st_mode) && includeSubFolders)
                for(const auto &file : getFiles(path, fileExtension, includeExtension, includeSubFolders)) {
                    result.push_back(file);
                }
            else{
                if(std::find(fileExtension.begin(), fileExtension.end(), path.substr(path.find_last_of('.')+1,path.size())) != fileExtension.end()){
                    std::string file = entry->d_name;
                    if (!includeExtension) file = file.substr(0, file.find_last_of('.'));
                    if (includeSubFolders) file = path;
                    result.emplace_back(file);
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