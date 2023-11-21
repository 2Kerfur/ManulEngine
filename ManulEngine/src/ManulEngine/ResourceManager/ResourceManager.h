#pragma once
#include <string>
#include <vector>

class ResourceManager {
public:
	inline bool FileExists(const std::string& name);
	static std::string GetWorkingDirectory();
	static bool LoadConfig(std::vector<std::string>& config, std::string path);
	static bool CreateConfig(std::vector<std::string>& config, std::string& path);
private:
	
};

