#pragma once
#include<string>

class Texture 
{
    unsigned int mTextureID;
    int mImageWidth, mImageHeight, mBitsPerPixel;
public:
    Texture(const std::string& imagePath);
    ~Texture();
    void setActiveTextureAndBind(unsigned int slot = 0) const;
    void unbindTexture() const;
};
