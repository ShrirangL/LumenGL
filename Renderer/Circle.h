#pragma once

#include "IDrawable.h"

class Circle : public IDrawable
{
	float mRadius;
	Vector mNormal;
public:
	Circle();
	Circle(float radius);
	Circle(float x, float y, float z, float radius);
	Circle(const Point& centre, float radius);
	Circle(const Point& centre, float radius, const Vector& normal);

	void setLayout() override;
	void setShapeType() override;
	void generateVerticesAndIndices() override;
};