#pragma once
#include "Point.h"
#include "IDrawable.h"

struct Line : public IDrawable
{
	Point start, end;

	Line();
	Line(const Point& start, const Point& end);
	Line(float stX, float stY, float stZ, float endX, float endY, float endZ);

	void setLayout() override;
	void setShapeType() override;
	void generateVerticesAndIndices() override;
};