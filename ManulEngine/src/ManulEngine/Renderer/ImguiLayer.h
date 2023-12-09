#pragma once
#include "Renderer.h"
namespace ManulEngine {
	class ImguiLayer
	{
	public:
		static int Init(Renderer::GraphicsAPI api);
		static void Render();
		static void Shutdown();
	private:

	};
}