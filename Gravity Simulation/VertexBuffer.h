#pragma once

class VertexBuffer
{
	unsigned int mVertexBufferID;
	unsigned int mVertexCount;
public:
	VertexBuffer();
	VertexBuffer(const void* data, unsigned int size, unsigned int cnt);
	~VertexBuffer();

	void setDataSizeAndCount(const void* data, unsigned int size, unsigned int cnt);
	void bindVertexBuffer() const;
	void unbindVertexBuffer() const;
	unsigned int getVertexCount() const;
};
