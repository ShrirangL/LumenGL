#include "IndexBuffer.h"
#include <GL/glew.h>

IndexBuffer::IndexBuffer()
	: mVertexCount(0)
{
	glGenBuffers(1, &mIndexBufferID);
}

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int vCount)
	: mVertexCount(vCount)
{
	glGenBuffers(1, &mIndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mVertexCount * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &mIndexBufferID);
}

void IndexBuffer::setDataAndCount(const unsigned int* data, unsigned int vCount)
{
	mVertexCount = vCount;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mVertexCount * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

void IndexBuffer::bindIndexBuffer() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferID);
}

void IndexBuffer::unbindIndexBuffer() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::getVertexCount() const
{
	return mVertexCount;
}