#pragma once
#include <string>
#include <vector>

class ResourceManager {
public:
	inline bool ResourceManager::FileExists(const std::string& name);
	static std::string GetWorkingDirectory();
	static bool LoadConfig(std::vector<std::string>& config, std::string path);
	//static bool CreateConfig(std::string config[], std::string& path);
	static bool CreateConfig(std::vector<std::string>& config, std::string& path);

};

