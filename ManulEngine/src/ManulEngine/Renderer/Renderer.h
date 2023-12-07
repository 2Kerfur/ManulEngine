#pragma once
#include "RendererBackend.h"
namespace ManulEngine {
	
	class Renderer
	{
	public:
		enum GpuCrashReason
		{
			None,				// Gpu didn't crash
			PageFault,			// VA Page Fault (invalid memory access)
			Hang,				// Hang (long-running shader/operation)
			OutOfMemory,		// Not enough memory for something
			Unknown,			// Gpu crashed for unknown reason
		};
		enum GraphicsAPI
		{
			OpenGL,
			Vulkan,
			DirectX
		};
		static bool Init(uint32_t windowWidht, uint32_t windowHegiht, GraphicsAPI api);
		static void SetWindowSize(uint32_t windowWidht, uint32_t windowHegiht);
		static void Shutdown();
		static void Render();

		static void OnWindowResize(uint32_t width, uint32_t height);
	private:
		static RendererBackend* backend;
	};
}