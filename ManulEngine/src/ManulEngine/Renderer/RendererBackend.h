#pragma once

class RendererBackend {
public:
    static void Init(uint32_t windowWidht, uint32_t windowHegiht);
    static void Shutdown();
    static void Render();
private:

};
