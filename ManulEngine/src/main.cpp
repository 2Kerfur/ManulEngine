#include "ManulEngine.h"
#include "ResourceManager/ResourcePacker.h"

int main(int argc, char *argv[])
{
    ManulEngine::Application application;

    ResourcePacker resourceLoader;
    Resource resource;
    resource.path = "D:\\text.txt";
    resource.type = Resource::Type::TextFile;

    resourceLoader.PackResource(resource, "D:\\");

    return 0;
	//application.Create(nullptr);
    //while (!application.applicationExit)
    //{
    //    application.Update();
    //}
}
