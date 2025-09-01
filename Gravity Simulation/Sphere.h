#pragma once

#include "IDrawable.h"

class Sphere : public IDrawable
{
	float mRadius;
public:
	Sphere(float radius);
	Sphere(float radius, float centreX, float centreY, float centreZ);
	Sphere(const Point& centre, float radius);

	void setShapeType() override;
	void generateVerticesAndIndices() override;
};
