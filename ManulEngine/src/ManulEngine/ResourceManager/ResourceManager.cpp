#include "ResourceManager.h"

inline bool ResourceManager::FileExists(const std::string& name) {
    if (FILE* file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    }
    else {
        return false;
    }
}
std::string ResourceManager::GetWorkingDirectory()
{
    return std::string();
}

std::vector<std::string> ResourceManager::LoadConfig(std::string path)
{
    
}
