#include "mapch.h"
#include "Renderer2D.h"
#include "RendererBackend.h"


void Renderer2D::Init(uint32_t windowWidht, uint32_t windowHegiht) {
    RendererBackend::Init(windowWidht, windowHegiht);
}

void Renderer2D::DrawQuad()
{
    RendererBackend::DrawQuad();
}

void Renderer2D::Shutdown() {

}

void Renderer2D::Render() {
    RendererBackend::Render();
}
