#pragma once
namespace ManulEngine {
    class RendererBackend {
    public:
        virtual ~RendererBackend() {};
        virtual bool Init(uint32_t windowWidht, uint32_t windowHegiht) { return true; };
        virtual void SetWindowSize(uint32_t windowWidht, uint32_t windowHeight) {};
        virtual void Render() {};
        virtual void Shutdown() {};
    };
}


