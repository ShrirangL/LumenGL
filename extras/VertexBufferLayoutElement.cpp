#include "VertexBufferLayoutElement.h"
#include <GL/glew.h>

VertexBufferLayoutElement::VertexBufferLayoutElement(unsigned int type, unsigned int count, unsigned char normalized)
    : mDataType(type), mDataCount(count), mNormalizedFlag(normalized)
{}

unsigned int VertexBufferLayoutElement::getSizeOfType(unsigned int type)
{
    switch (type)
    {
        case GL_FLOAT: return 4;
        case GL_UNSIGNED_INT: return 4;
        case GL_UNSIGNED_BYTE: return 1;
    }
    return 0;
}

unsigned char VertexBufferLayoutElement::getNormalizedFlagOfType(unsigned int type)
{
    switch (type)
    {
    case GL_FLOAT: return GL_FALSE;
    case GL_UNSIGNED_INT: return GL_FALSE;
    case GL_UNSIGNED_BYTE: return GL_TRUE;
    }
    return 0;
}

unsigned int VertexBufferLayoutElement::getDataType() const
{
    return mDataType;
}
unsigned int VertexBufferLayoutElement::getDataCount() const
{
    return mDataCount;
}
unsigned char VertexBufferLayoutElement::getNormalizedFlag() const
{
    return mNormalizedFlag;
}
