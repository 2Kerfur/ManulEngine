#pragma once
#include <string>

struct Resource
{
    std::string path;
    enum Type
    {
        Scene,
        Texture,
        Model,
        TextFile
    };
    Type type;
};

