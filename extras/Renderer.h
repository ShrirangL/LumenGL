#pragma once

class VertexArray;
class VertexBuffer;
class IndexBuffer;
class Program;

enum FillMode
{
	FILL = 0, EDGE, FILL_AND_EDGE
};

class Renderer
{
	Renderer();
	Renderer(const Renderer& other) = delete;
	Renderer& operator=(const Renderer& other) = delete;
public:
	static Renderer& getInstance();
	void clearScreen() const;
	void drawObject(const VertexArray& va, const VertexBuffer& vb, const IndexBuffer* ib, const Program& fillProgram, const Program* edgeProgram, FillMode fillMode, unsigned int drawMode) const;
	void drawObject(unsigned int drawMode, const IndexBuffer* ib, unsigned int vertexCount) const;
};