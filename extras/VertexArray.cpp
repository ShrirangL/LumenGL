#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "VertexBufferLayoutElement.h"
#include <GL/glew.h>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &mVertexArrayID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &mVertexArrayID);
}

void VertexArray::addBufferAndLayout(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	bindVertexArray();
	vb.bindVertexBuffer();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (int i = 0; i < elements.size(); i++) 
	{
		const auto& element = elements[i];
		glVertexAttribPointer(i, element.getDataCount(), element.getDataType(), element.getNormalizedFlag(), layout.getStrideInBytes(), (void*)offset);
		glEnableVertexAttribArray(i);
		offset += element.getDataCount() * VertexBufferLayoutElement::getSizeOfType(element.getDataType());
	}
}

void VertexArray::bindVertexArray() const
{
	glBindVertexArray(mVertexArrayID);
}

void VertexArray::unbindVertexArray() const
{
	glBindVertexArray(0);
}
