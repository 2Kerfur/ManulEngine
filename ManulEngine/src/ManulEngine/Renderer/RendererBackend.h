#pragma once
namespace ManulEngine {
    class RendererBackend {
    public:
        virtual ~RendererBackend() {};
        virtual bool Init(Vector2Uint windowSize) { return true; };
        virtual void SetWindowSize(Vector2Uint windowSize) {};
        virtual void Render() {};
        virtual void Shutdown() {};
    };
}


