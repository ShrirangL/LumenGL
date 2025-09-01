#pragma once

#include <glm/glm.hpp>

struct Point
{
	float x, y, z;
	Point() : x(0.0f), y(0.0f), z(0.0f) {}
	Point(float f) : x(f), y(f), z(f) {}
	Point(float x, float y, float z) : x(x), y(y), z(z) {}
	Point(const Point& other) : x(other.x), y(other.y), z(other.z) {}
	Point(const glm::vec3& other) : x(other.x), y(other.y), z(other.z) {}

	Point operator+(const Point& other) const
	{
		return Point(x + other.x, y + other.y, z + other.z);
	}

	// Conversion operator to glm::vec3
	operator glm::vec3() const 
	{
		return glm::vec3(x, y, z);
	}

	Point mid(const Point& other) const
	{
		return Point((x + other.x) / 2.0f, (y + other.y) / 2.0f, (z + other.z) / 2.0f);
	}

	float distance(const Point& other) const
	{
		return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + (z - other.z) * (z - other.z));	
	}
};

typedef Point Vector;