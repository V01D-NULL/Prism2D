#pragma once

#include <GL/glew.h>
#include <cstdint>

/* Thanks to https://gamedev.stackexchange.com/a/140704 for a short and consise answer on how to render a scene in ImGui */
namespace GLrenderer
{
    class GL_FBO
    {
        public:
            GL_FBO();

        private:
            void genFBO();
            void genTexture();

        public:
            std::uint32_t getTex();
            void bindFBO();
            void unbindFBO();
            void Destroy();

        private:
            std::uint32_t fbo;
            std::uint32_t texture;
            bool was_fbo_generated = false;
    };
}