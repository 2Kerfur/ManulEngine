#include "ManulEngine.h"

int main(int argc, char *argv[])
{
    ManulEngine::Application application;

	application.Create();
    while (!application.applicationExit)
    {
        application.Update();
    }
    return 0;
}

