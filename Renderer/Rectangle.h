#pragma once

#include "IDrawable.h"
#include "Point.h"

class Rectangle : public IDrawable
{
	Point mLeftBottom, mTopRight;
	float mWidth, mHeight;
	Vector mNormal;
public:
	Rectangle();
	Rectangle(float width, float height);
	Rectangle(const Point& centre, float width, float height);
	Rectangle(const Point& leftBottom, const Point& topRight);
	Rectangle(const Point& leftBottom, const Point& topRight, const Vector& normal);
	Rectangle(float leftX, float leftY, float leftZ, float rightX, float rightY, float rightZ);

	void setLayout() override;
	void setShapeType() override;
	void generateVerticesAndIndices() override;
};
