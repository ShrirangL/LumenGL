#include "Texture.h"
#include<GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& path) {
    unsigned char* buffer = stbi_load(path.c_str(), &mImageWidth, &mImageHeight, &mBitsPerPixel, 4);
    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mImageWidth, mImageHeight, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(buffer);
}

Texture::~Texture() {
    glDeleteTextures(1, &mTextureID);
}

void Texture::setActiveTextureAndBind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
}

void Texture::unbindTexture() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
