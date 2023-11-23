#include "ResourceManager.h"
#include "mapch.h"
#include <fstream>
#include <iterator>
#include <sstream>
inline bool ResourceManager::FileExists(const std::string& path) {
    if (std::filesystem::exists(path)) return true;
    else return false;
}
std::string ResourceManager::GetWorkingDirectory()
{
    return std::filesystem::current_path().string();
}

bool ResourceManager::LoadConfig(std::vector<std::string>& config, std::string path)
{
    std::ifstream file_in(path);
    if (!file_in) {
        M_CORE_ERROR("Log file not found, path: ", path);
        return false;
    }

    std::string line;
    while (std::getline(file_in, line))
        config.push_back(line);

    file_in.close();
    return true;
}
bool ResourceManager::CreateConfig(std::vector<std::string>& config, std::string& path)
{
    std::remove(path.c_str());
    std::ofstream outfile(path);
    
    for (std::string var : config)
        outfile << var << std::endl;
        
    outfile.close();
    return true;
}
