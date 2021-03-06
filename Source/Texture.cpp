#include "Texture.h"

rfe::Texture::Texture(const std::string& path,
                      int textureType,
                      int wrapping,
                      int filtering,
                      int inColorType,
                      int outColorType,
                      bool flip)
{
    textureTypeID = textureType;
    textureID = 0;
    CreateTexture(path.data(), textureType, wrapping, filtering, inColorType, outColorType, flip);
}

void rfe::Texture::CreateTexture(const char* path,
                                 int textureType,
                                 int wrapping,
                                 int filtering,
                                 int inColorType,
                                 int outColorType,
                                 bool flip)
{
    glGenTextures(1, &textureID);
    glBindTexture(textureType, textureID);

    glTexParameteri(textureType, GL_TEXTURE_WRAP_S, wrapping);
    glTexParameteri(textureType, GL_TEXTURE_WRAP_T, wrapping);

    glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, filtering);
    glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, filtering);

    int width, height, nrChannels;

    stbi_set_flip_vertically_on_load(flip);

    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if(data != nullptr)
    {
        glTexImage2D(textureType, 0, inColorType, width, height, 0, outColorType, GL_UNSIGNED_BYTE,  data);
        glGenerateMipmap(textureType);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
    glBindTexture(textureType, 0);
}

void rfe::Texture::Bind() const
{
    glBindTexture(textureTypeID, textureID);
}

void rfe::Texture::Unbind() const
{
    glBindTexture(textureTypeID, 0);
}

void rfe::Texture::ActivateTexture(unsigned int textureNumber)
{
    glActiveTexture(textureNumber);
}
