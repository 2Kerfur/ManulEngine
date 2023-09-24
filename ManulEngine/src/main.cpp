#include "ManulEngine.h"
#include "ManulEngine/ResourceManager/ResourcePacker.h"

int main(int argc, char *argv[])
{
    ManulEngine::Application application;

    ResourcePacker resourceLoader;
    Resource resource;
    resource.path = "D:\\text.txt";
    resource.type = Resource::Type::TextFile;

    //resourceLoader.PackResource(resource, "D:\\");


	application.Create(nullptr);
    while (!application.applicationExit)
    {
        application.Update();
    }
    return 0;
}

