#pragma once

#include "IDrawable.h"

class Cuboid : public IDrawable
{
	float mWidth, mHeight, mDepth;
public:
	Cuboid(float width, float height, float depth);
	Cuboid(const Point& centre, float width, float height, float depth);
	Cuboid(float centreX, float centreY, float centreZ, float width, float height, float depth);

	void setShapeType() override;
	void generateVerticesAndIndices() override;
};