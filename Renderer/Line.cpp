#include "Line.h"

Line::Line() 
	: start(), end() 
{
	IDrawable::build();
}

Line::Line(const Point& start, const Point& end)
	: start(start), end(end) 
{
	IDrawable::build();
} 

Line::Line(float stX, float stY, float stZ, float endX, float endY, float endZ)
	:start(stX, stY, stZ), end(endX, endY, endZ) 
{
	IDrawable::build();
}

void Line::setLayout()
{
	IDrawable::setVBLLayout3Floats();
}

void Line::setShapeType()
{
	IDrawable::setShapeType2D();
}

void Line::generateVerticesAndIndices()
{
	mVertices.push_back(start.x);
	mVertices.push_back(start.y);
	mVertices.push_back(start.z);

	mVertices.push_back(end.x);
	mVertices.push_back(end.y);
	mVertices.push_back(end.z);

	mIndices.push_back(0);
	mIndices.push_back(1);
}
