#pragma once

class IndexBuffer
{
	unsigned int mIndexBufferID;
	unsigned int mVertexCount;
public:
	IndexBuffer();
	IndexBuffer(const unsigned int* data, unsigned int vCount);
	~IndexBuffer();

	void setDataAndCount(const unsigned int* data, unsigned int vCount);
	void bindIndexBuffer() const;
	void unbindIndexBuffer() const;
	unsigned int getVertexCount() const;
};
