#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
	unsigned int mVertexArrayID;
public:
	VertexArray();
	~VertexArray();

	void addBufferAndLayout(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void bindVertexArray() const;
	void unbindVertexArray() const;
};