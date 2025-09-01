#include "Renderer.h"
#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Program.h"

Renderer::Renderer() {}

Renderer& Renderer::getInstance()
{
	static Renderer instance;
	return instance;
}

void Renderer::clearScreen() const
{
	glClearColor(0.5f, 0.5f, 0.5f, 0.5f); // Grey background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);;
}

void Renderer::drawObject(const VertexArray& va, const VertexBuffer& vb, const IndexBuffer* ib, const Program& fillProgram, const Program* edgeProgram,
	FillMode fillMode, unsigned int drawMode) const
{
	va.bindVertexArray();

	switch (fillMode) {
	case FILL:
		fillProgram.useProgram();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		drawObject(drawMode, ib, vb.getVertexCount());
		break;

	case EDGE:
		if (edgeProgram) {
			edgeProgram->useProgram();
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			drawObject(drawMode, ib, vb.getVertexCount());
		}
		break;

	case FILL_AND_EDGE:
		// Fill pass
		fillProgram.useProgram();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		drawObject(drawMode, ib, vb.getVertexCount());

		// Edge pass (with slight offset to avoid z-fighting)
		if (edgeProgram) {
			glEnable(GL_POLYGON_OFFSET_LINE);
			glPolygonOffset(-1.0f, -1.0f);

			edgeProgram->useProgram();
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			drawObject(drawMode, ib, vb.getVertexCount());

			glDisable(GL_POLYGON_OFFSET_LINE);     // Clean up state
		}
		break;
	}
}

void Renderer::drawObject(unsigned int drawMode, const IndexBuffer* ib, unsigned int vertexCount) const
{
	if (ib)
	{
		ib->bindIndexBuffer();
		glDrawElements(drawMode, ib->getVertexCount(), GL_UNSIGNED_INT, nullptr);
	}
	else
	{
		glDrawArrays(drawMode, 0, vertexCount);
	}
}
