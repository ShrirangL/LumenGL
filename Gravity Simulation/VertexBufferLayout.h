#pragma once
#include <GL/glew.h>
#include "VertexBufferLayoutElement.h"
#include <vector>

class VertexBufferLayout
{
	unsigned int mVertexStride;
	std::vector<VertexBufferLayoutElement> mLayoutElements;

public:
	VertexBufferLayout();

	const std::vector<VertexBufferLayoutElement>& getElements() const;
	unsigned int getStrideInBytes() const;
	unsigned int getStrideInFloats() const;
	void pushVertexBufferLayoutElement(unsigned int type, unsigned int count);
};