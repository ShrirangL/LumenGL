#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout()
	: mVertexStride(0)
{}

const std::vector<VertexBufferLayoutElement>& VertexBufferLayout::getElements() const
{
	return mLayoutElements;
}

unsigned int VertexBufferLayout::getStrideInBytes() const
{
	return mVertexStride;
}

unsigned int VertexBufferLayout::getStrideInFloats() const
{
	return mVertexStride/sizeof(float);
}

void VertexBufferLayout::pushVertexBufferLayoutElement(unsigned int type, unsigned int count)
{
	mLayoutElements.push_back({ type, count, VertexBufferLayoutElement::getNormalizedFlagOfType(type)});
	mVertexStride += count * VertexBufferLayoutElement::getSizeOfType(type);
}
