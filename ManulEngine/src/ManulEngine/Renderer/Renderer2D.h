#include "GLFW/glfw3.h"
class Renderer2D {
public:
    static void Init(uint32_t windowWidht, uint32_t windowHegiht, GLFWwindow* window);
    static void Shutdown();
    static void Render();
};
