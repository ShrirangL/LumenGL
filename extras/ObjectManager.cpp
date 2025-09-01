#include "ObjectManager.h"
#include "Line.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Cuboid.h"
#include "Cylinder.h"
#include "Sphere.h"

void ObjectManager::createLine(const Point& start, const Point& end)
{
	std::unique_ptr<IDrawable> line = std::make_unique<Line>(start, end);
	line->setPrograms(oldVertexShaderSource.data(), edgeFragmentShaderSource.data(),
		oldVertexShaderSource.data(), edgeFragmentShaderSource.data());
	mObjects.push_back(std::move(line));
}

void ObjectManager::createTriangle(const Point& p1, const Point& p2, const Point& p3)
{
	std::unique_ptr<IDrawable> triangle = std::make_unique <Triangle>(p1, p2, p3);
	triangle->setPrograms(oldVertexShaderSource.data(), edgeFragmentShaderSource.data(),
		oldVertexShaderSource.data(), edgeFragmentShaderSource.data());
	mObjects.push_back(std::move(triangle));
}

void ObjectManager::createRectangle(const Point& bottomLeft, const Point& topRight)
{
	std::unique_ptr<IDrawable> rectangle = std::make_unique <Rectangle>(bottomLeft, topRight);
	rectangle->setPrograms(oldVertexShaderSource.data(), edgeFragmentShaderSource.data(),
		oldVertexShaderSource.data(), edgeFragmentShaderSource.data());
	mObjects.push_back(std::move(rectangle));
}

void ObjectManager::createCircle(const Point& centre, float radius)
{
	std::unique_ptr<IDrawable> circle = std::make_unique <Circle>(centre, radius);
	circle->setPrograms(oldVertexShaderSource.data(), edgeFragmentShaderSource.data(),
		oldVertexShaderSource.data(), edgeFragmentShaderSource.data());
	mObjects.push_back(std::move(circle));
}

void ObjectManager::createCuboid(const Point& centre, float width, float height, float depth)
{
	std::unique_ptr<IDrawable> cuboid = std::make_unique <Cuboid>(centre, width, height, depth);
	cuboid->setPrograms(vertexShaderSource.data(), planetFragmentShaderSource.data(),
		vertexShaderSource.data(), edgeFragmentShaderSource.data());
	mObjects.push_back(std::move(cuboid));
}

void ObjectManager::createCylinder(const Point& bottomCentre, const Point& topCentre, float radius)
{
	std::unique_ptr<IDrawable> cylinder = std::make_unique <Cylinder>(bottomCentre, topCentre, radius);
	cylinder->setPrograms(vertexShaderSource.data(), planetFragmentShaderSource.data(),
		vertexShaderSource.data(), edgeFragmentShaderSource.data());
	mObjects.push_back(std::move(cylinder));
}

void ObjectManager::createSphere(const Point& centre, float radius)
{
	std::unique_ptr<IDrawable> sphere = std::make_unique <Sphere>(centre, radius);
	sphere->setPrograms(vertexShaderSource.data(), planetFragmentShaderSource.data(),
		vertexShaderSource.data(), edgeFragmentShaderSource.data());
	mObjects.push_back(std::move(sphere));
}

const std::vector<std::unique_ptr<IDrawable>>& ObjectManager::getShapes() const
{
	return mObjects;
}

void ObjectManager::drawShapes() const
{
	for (auto& shape : mObjects)
	{
		if (shape)
		{
			shape->draw();
		}
	}
}
