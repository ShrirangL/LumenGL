#pragma once

class VertexBufferLayoutElement
{
	unsigned int mDataType;
	unsigned int mDataCount;
	unsigned char mNormalizedFlag;

public:
	VertexBufferLayoutElement(unsigned int type, unsigned int count, unsigned char normalized);

	static unsigned int getSizeOfType(unsigned int type);
	static unsigned char getNormalizedFlagOfType(unsigned int type);

	unsigned int getDataType() const;
	unsigned int getDataCount() const;
	unsigned char getNormalizedFlag() const;
};
