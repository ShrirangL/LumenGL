#include "VertexBuffer.h"
#include <GL/glew.h>

VertexBuffer::VertexBuffer()
	: mVertexCount(0)
{
	glGenBuffers(1, &mVertexBufferID);
}

VertexBuffer::VertexBuffer(const void* data, unsigned int size, unsigned int cnt)
	: mVertexCount(cnt)
{
	glGenBuffers(1, &mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &mVertexBufferID);
}

void VertexBuffer::setDataSizeAndCount(const void* data, unsigned int size, unsigned int cnt)
{
	mVertexCount = cnt;
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::bindVertexBuffer() const
{
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
}

void VertexBuffer::unbindVertexBuffer() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int VertexBuffer::getVertexCount() const
{
	return mVertexCount;
}