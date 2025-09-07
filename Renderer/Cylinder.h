#pragma once

#include "IDrawable.h"
#include "Point.h"

class Cylinder : public IDrawable
{
	Point topCentre, bottomCentre;
	float height;
	float radius;
public:
	Cylinder(float height, float radius);
	Cylinder(const Point& point, float height, float radius);
	Cylinder(const Point& tCentre, const Point& bCentre, float radius);

	void setShapeType() override;
	void generateVerticesAndIndices() override;
};