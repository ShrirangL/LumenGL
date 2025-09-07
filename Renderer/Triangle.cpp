#include "Triangle.h"

Triangle::Triangle()
	: IDrawable(), p1(), p2(), p3(), mNormal(0.0f, 0.0f, 1.0f)
{
	IDrawable::build();
}

Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3)
	: IDrawable((p1.x + p2.x + p3.x) / 3.0f, (p1.y + p2.y + p3.y) / 3.0f, (p1.z + p2.z + p3.z) / 3.0f), 
	p1(p1), p2(p2), p3(p3), mNormal(0.0f, 0.0f, 1.0f)
{
	IDrawable::build();
}

Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3, const Vector& normal)
	: IDrawable((p1.x + p2.x + p3.x) / 3.0f, (p1.y + p2.y + p3.y) / 3.0f, (p1.z + p2.z + p3.z) / 3.0f),
	p1(p1), p2(p2), p3(p3), mNormal(normal)
{
	IDrawable::build();
}

Triangle::Triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
	: IDrawable((x1 + x2 + x3) / 3.0f, (y1 + y2 + y3) / 3.0f, (z1 + z2 + z3) / 3.0f),
	p1(x1, y1, z1), p2(x2, y2, z2), p3(x3, y3, z3), mNormal(0.0f, 0.0f, 1.0f)
{
	IDrawable::build();
}

void Triangle::setLayout()
{
	IDrawable::setVBLLayout3Floats();
}

void Triangle::setShapeType()
{
	IDrawable::setShapeType2D();
}

void Triangle::generateVerticesAndIndices()
{
	mVertices.clear();
	mIndices.clear();

	mVertices.push_back(p1.x);
	mVertices.push_back(p1.y);
	mVertices.push_back(p1.z);
	mVertices.push_back(p2.x);
	mVertices.push_back(p2.y);
	mVertices.push_back(p2.z);
	mVertices.push_back(p3.x);
	mVertices.push_back(p3.y);
	mVertices.push_back(p3.z);

	mIndices.push_back(0);
	mIndices.push_back(1);
	mIndices.push_back(1);
	mIndices.push_back(2);
	mIndices.push_back(2);
	mIndices.push_back(0);
}
