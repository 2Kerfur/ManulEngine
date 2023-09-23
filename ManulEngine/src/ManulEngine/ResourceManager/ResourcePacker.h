#include "Resource.h"

class ResourcePacker {
public:
    int PackResource(Resource resource, std::string destination_path);
    void Update();
private:
    std::vector<Resource> resources;
};

