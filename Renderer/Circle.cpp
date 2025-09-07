#include "Circle.h"
#include "glm/glm.hpp"
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/epsilon.hpp>

Circle::Circle()
	: IDrawable(), mRadius(1.0), mNormal(0.0, 0.0, 1.0)
{
	IDrawable::build();
}

Circle::Circle(float radius)
	: IDrawable(), mRadius(radius), mNormal(0.0, 0.0, 1.0)
{
	IDrawable::build();
}

Circle::Circle(float x, float y, float z, float radius)
	: IDrawable(x, y, z), mRadius(radius), mNormal(0.0, 0.0, 1.0)
{
    IDrawable::build();
}

Circle::Circle(const Point& centre, float radius)
	: IDrawable(centre), mRadius(radius), mNormal(0.0, 0.0, 1.0)
{
	IDrawable::build();
}

Circle::Circle(const Point& centre, float radius, const Vector& normal)
	: IDrawable(centre), mRadius(radius), mNormal(normal)
{
	IDrawable::build();
}

void Circle::setLayout()
{
	IDrawable::setVBLLayout3Floats();
}

void Circle::setShapeType()
{
	IDrawable::setShapeType2D();
}

void Circle::generateVerticesAndIndices()
{
    glm::vec3 n = glm::normalize(glm::vec3(mNormal.x, mNormal.y, mNormal.z));
    glm::vec3 tangent;

    // Pick an arbitrary vector that's not parallel to the normal
    if (glm::all(glm::epsilonEqual(n, glm::vec3(0.0f, 0.0f, 1.0f), 1e-4f))) {
        tangent = glm::vec3(1, 0, 0);
    }
    else {
        tangent = glm::normalize(glm::cross(n, glm::vec3(0, 0, 1)));
    }

    glm::vec3 bitangent = glm::cross(n, tangent);

    size_t segments = 100;

    std::vector<glm::vec3> vertices;
    for (int i = 0; i < segments; ++i) {
        float angle = glm::two_pi<float>() * i / segments;
        glm::vec3 point = mCentre
            + mRadius * cos(angle) * tangent
            + mRadius * sin(angle) * bitangent;
        mVertices.push_back(point.x);
        mVertices.push_back(point.y);
        mVertices.push_back(point.z);
    }

    for (int i = 0; i < segments; i++)
    {
		mIndices.push_back(i);
        if (i < segments - 1)
            mIndices.push_back(i + 1);
        else
            mIndices.push_back(0);
    }
}




