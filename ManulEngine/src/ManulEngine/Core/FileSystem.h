#pragma once
#include <filesystem>
#include <string>

namespace ManulEngine {
    class FileSystem {
    public:
        static std::string ReadConfigFile (const std::filesystem::path& filepath);
        static std::string WriteConfigFile (const std::filesystem::path& filepath);
    };
}
