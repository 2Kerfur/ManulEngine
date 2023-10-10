#pragma once
#include <string>
#include <vector>

class ResourceManager {
public:
	inline bool ResourceManager::FileExists(const std::string& name);
	static std::string GetWorkingDirectory();
	static std::vector<std::string> LoadConfig(std::string path);
	
};

