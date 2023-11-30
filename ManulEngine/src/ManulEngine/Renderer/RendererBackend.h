#pragma once
namespace ManulEngine {
    class RendererBackend {
    public:
        virtual ~RendererBackend() {};
        virtual bool Init(uint32_t windowWidht, uint32_t windowHegiht) { return true; };
        virtual void Render() {};
        virtual void Shutdown() {};
    };
}


