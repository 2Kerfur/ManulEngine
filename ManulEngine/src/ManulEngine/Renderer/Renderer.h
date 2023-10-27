#pragma once
namespace ManulEngine {
	class Renderer
	{
	public:
		static bool Init(uint32_t windowWidht, uint32_t windowHegiht);
		
		static void Shutdown();
		static void Render();

		static void OnWindowResize(uint32_t width, uint32_t height);
	private:
		
	};
}