#ifndef PROJECT_SWA_FILEMANAGER_H
#define PROJECT_SWA_FILEMANAGER_H

#include <string>
#include <vector>

class FileManager
{
public:
    std::vector<std::string> getFiles(const std::string& path, const std::string &fileExtension) const;
    std::vector<std::string> getFilesWithoutExtension(const std::string& path, const std::string &fileExtension) const;

    ~FileManager();
    FileManager();
};

#endif //PROJECT_SWA_FILEMANAGER_H
