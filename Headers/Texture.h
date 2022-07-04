#ifndef REFRAENGINE_TEXTURE_H
#define REFRAENGINE_TEXTURE_H

#include <iostream>

#include "Renderer.h"
#include "stb_image.h"

namespace rfe
{
    class Texture
    {
    private:
        unsigned int textureID;
        unsigned int textureTypeID;
    public:
        Texture(const std::string path,
                unsigned int textureType = GL_TEXTURE_2D,
                unsigned int wrapping = GL_REPEAT,
                unsigned int filtering = GL_NEAREST,
                unsigned int inColorType = GL_RGB,
                unsigned int outColorType = GL_RGB,
                bool flip = false);
        void CreateTexture(const char* path,
                           unsigned int textureType = GL_TEXTURE_2D,
                           unsigned int wrapping = GL_REPEAT,
                           unsigned int filtering = GL_NEAREST,
                           unsigned int inColorType = GL_RGB,
                           unsigned int outColorType = GL_RGB,
                           bool flip = false);
        void Bind();
        void Unbind();
        void ActivateTexture(unsigned int textureNumber = 0);
    };
}

#endif //REFRAENGINE_TEXTURE_H
