#include "Rectangle.h"

Rectangle::Rectangle()
	: IDrawable(), mLeftBottom(0.0f, 0.0f, 0.0f), mTopRight(1.0f, 1.0f, 0.0f), mWidth(1.0f), mHeight(1.0f), mNormal(0.0f, 0.0f, 1.0f)
{
	IDrawable::build();
}

Rectangle::Rectangle(float width, float height)
	: IDrawable(0.0f, 0.0f, 0.0f), mLeftBottom(-width / 2.0f, -height / 2.0f, 0.0f), mTopRight(width / 2.0f, height / 2.0f, 0.0f),
	mWidth(width), mHeight(height), mNormal(0.0f, 0.0f, 1.0f)
{
	IDrawable::build();
}

Rectangle::Rectangle(const Point& centre, float width, float height)
	:IDrawable(centre), mLeftBottom(centre.x - width / 2.0f, centre.y - height / 2.0f, centre.z),
	mTopRight(centre.x + width / 2.0f, centre.y + height / 2.0f, centre.z), mWidth(width), mHeight(height), mNormal(0.0f, 0.0f, 1.0f)
{
	IDrawable::build();
}

Rectangle::Rectangle(const Point& leftBottom, const Point& topRight)
	: IDrawable((leftBottom.x + topRight.x) / 2.0f, (leftBottom.y + topRight.y) / 2.0f, (leftBottom.z + topRight.z) / 2.0f),
	  mLeftBottom(leftBottom), mTopRight(topRight), mWidth(topRight.x - leftBottom.x), mHeight(topRight.y - leftBottom.y), mNormal(0.0f, 0.0f, 1.0f)
{
	IDrawable::build();
}

Rectangle::Rectangle(const Point& leftBottom, const Point& topRight, const Vector& normal)
	: IDrawable((leftBottom.x + topRight.x) / 2.0f, (leftBottom.y + topRight.y) / 2.0f, (leftBottom.z + topRight.z) / 2.0f),
	mLeftBottom(leftBottom), mTopRight(topRight), mWidth(topRight.x - leftBottom.x), mHeight(topRight.y - leftBottom.y), mNormal(normal)
{
	IDrawable::build();
}

Rectangle::Rectangle(float leftX, float leftY, float leftZ, float rightX, float rightY, float rightZ)
	: IDrawable((leftX + rightX) / 2.0f, (leftY + rightY) / 2.0f, (leftZ + rightZ) / 2.0f),
	mLeftBottom(leftX, leftY, leftZ), mTopRight(rightX, rightY, rightZ), mWidth(rightX - leftX), mHeight(rightY - leftY), mNormal(0.0f, 0.0f, 1.0f)
{
	IDrawable::build();
}

void Rectangle::setLayout()
{
	IDrawable::setVBLLayout3Floats();
}

void Rectangle::setShapeType()
{
	IDrawable::setShapeType2D();
}

void Rectangle::generateVerticesAndIndices()
{
	Point bottomRight(mLeftBottom.x + mWidth, mLeftBottom.y, mLeftBottom.z);
	Point topLeft(mLeftBottom.x, mLeftBottom.y + mHeight, mLeftBottom.z);

	mVertices.push_back(mLeftBottom.x);
	mVertices.push_back(mLeftBottom.y);
	mVertices.push_back(mLeftBottom.z);
	mVertices.push_back(bottomRight.x);
	mVertices.push_back(bottomRight.y);
	mVertices.push_back(bottomRight.z);
	mVertices.push_back(mTopRight.x);
	mVertices.push_back(mTopRight.y);
	mVertices.push_back(mTopRight.z);
	mVertices.push_back(topLeft.x);
	mVertices.push_back(topLeft.y);
	mVertices.push_back(topLeft.z);

	mIndices.push_back(0);
	mIndices.push_back(1);
	mIndices.push_back(1);
	mIndices.push_back(2);
	mIndices.push_back(2);
	mIndices.push_back(3);
	mIndices.push_back(3);
	mIndices.push_back(0);
}
