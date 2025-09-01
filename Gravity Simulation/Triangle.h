#pragma once

#include "IDrawable.h"
#include "Point.h"

class Triangle : public IDrawable
{
	Point p1, p2, p3;
	Vector mNormal;
public:
	Triangle();
	Triangle(const Point& p1, const Point& p2, const Point& p3);
	Triangle(const Point& p1, const Point& p2, const Point& p3, const Vector& normal);
	Triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
	void setLayout() override;
	void setShapeType() override;
	void generateVerticesAndIndices() override;
};