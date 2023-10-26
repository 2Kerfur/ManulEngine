#include "mapch.h"
#include "RendererBackend.h"
#include "Platform/OpenGL/OpenGLBackend.h"

void RendererBackend::Init(uint32_t windowWidht, uint32_t windowHegiht) {
    OpenGLBackend::Init(windowWidht, windowHegiht);
}

void RendererBackend::Shutdown() {

}

void RendererBackend::Render() {
    OpenGLBackend::Render();
}
