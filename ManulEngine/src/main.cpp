#include "ManulEngine.h"

int main(int argc, char *argv[])
{
    ManulEngine::Application application;

	application.Create(nullptr);

    while (!application.applicationExit)
    {
        application.Update();
    }
}
