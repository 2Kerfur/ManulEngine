#pragma once
#include <cstdint>
class Renderer2D {
public:
    static void Init(uint32_t windowWidht, uint32_t windowHegiht);
    static void DrawQuad();
    static void Shutdown();
    static void Render();
private:

};
