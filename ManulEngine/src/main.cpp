#include "Window.h"

int main(void)
{
	
	Window window;
	window.Create(600, 600, "ManulEngine", false);

	while (!window.windowShouldClose)
	{
		window.Update();
	}
}
