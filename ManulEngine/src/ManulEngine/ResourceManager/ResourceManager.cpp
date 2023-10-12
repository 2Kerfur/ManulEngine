#include "ResourceManager.h"
#include <fstream>
#include <iterator>
#include <sstream>
inline bool ResourceManager::FileExists(const std::string& name) {
    if (FILE* file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    }
    else {
        return false;
    }
    return true;
}
std::string ResourceManager::GetWorkingDirectory()
{
    return std::filesystem::current_path().string();
}

bool ResourceManager::LoadConfig(std::vector<std::string>& config, std::string path)
{
    std::ifstream file_in(path);
    if (!file_in) {
        std::cout << "file not found: Path: " << path;
        return false;
    }

    std::string line;
    while (std::getline(file_in, line))
        config.push_back(line);
    
    return true;
}

bool ResourceManager::CreateConfig(std::vector<std::string>& config, std::string& path)
{
    std::ofstream outfile(path);

    for (int i = 0; i < config.size(); i++)
        outfile << config[i] << std::endl;
        
    outfile.close();
    return true;
}
