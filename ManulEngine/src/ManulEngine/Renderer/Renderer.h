#pragma once
#include "RendererBackend.h"
namespace ManulEngine {
	
	class Renderer
	{
	public:
		enum GraphicsAPI
		{
			OpenGL,
			Vulkan,
			DirectX
		};
		static bool Init(uint32_t windowWidht, uint32_t windowHegiht, GraphicsAPI api);
		static void Shutdown();
		static void Render();

		static void OnWindowResize(uint32_t width, uint32_t height);
	private:
		static RendererBackend* backend;
	};
}