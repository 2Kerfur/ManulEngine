#pragma once
#include "RendererBackend.h"
#include "ManulEngine/Core/Math/Math.h"
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
		static bool Init(Vector2Uint windowSize, GraphicsAPI api);
		static void SetWindowSize(Vector2Uint windowSize);
		static void Shutdown();
		static void Render();
	private:
		static RendererBackend* backend;
	};
}