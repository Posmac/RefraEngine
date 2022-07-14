#ifndef REFRAENGINE_TEXTURE_H
#define REFRAENGINE_TEXTURE_H

#include <iostream>

#include "Render.h"
#include "stb_image.h"

namespace rfe
{
    class Texture
    {
    private:
        unsigned int textureID;
        unsigned int textureTypeID;
    public:
        Texture(const std::string& path,
                int textureType = GL_TEXTURE_2D,
                int wrapping = GL_REPEAT,
                int filtering = GL_NEAREST,
                int inColorType = GL_RGB,
                int outColorType = GL_RGB,
                bool flip = false);
        void CreateTexture(const char* path,
                           int textureType = GL_TEXTURE_2D,
                           int wrapping = GL_REPEAT,
                           int filtering = GL_NEAREST,
                           int inColorType = GL_RGB,
                           int outColorType = GL_RGB,
                           bool flip = false);
        void Bind() const;
        void Unbind() const;
        void ActivateTexture(unsigned int textureNumber = 0);
    };
}

#endif //REFRAENGINE_TEXTURE_H
