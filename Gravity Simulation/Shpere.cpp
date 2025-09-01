#include "Sphere.h"

Sphere::Sphere(float radius)
	: IDrawable(), mRadius(radius)
{
	IDrawable::build();
}

Sphere::Sphere(float radius, float centreX, float centreY, float centreZ)
	: IDrawable(centreX, centreY, centreZ), mRadius(radius)
{
	IDrawable::build();
}

Sphere::Sphere(const Point& centre, float radius)
	:IDrawable(centre), mRadius(radius)
{
	IDrawable::build();
}

void Sphere::setShapeType()
{
	mShapeType = ShapeType::Shape3D;
}

void Sphere::generateVerticesAndIndices()
{
    mVertices.clear();
    mIndices.clear();

    constexpr unsigned int stacks = 32, slices = 32;
    glm::vec3 sphereCentre(mCentre.x, mCentre.y, mCentre.z);

    for (unsigned int i = 0; i <= stacks; ++i) {
        float phi = PI * static_cast<float>(i) / static_cast<float>(stacks);

        for (unsigned int j = 0; j <= slices; ++j) {
            float theta = 2.0f * PI * static_cast<float>(j) / static_cast<float>(slices);

            float x = sin(phi) * cos(theta);
            float y = cos(phi);
            float z = sin(phi) * sin(theta);

            glm::vec3 normal = glm::normalize(glm::vec3(x, y, z));
            glm::vec3 position = sphereCentre + mRadius * normal;

            // Texture coordinates (u,v)
            float u = static_cast<float>(j) / static_cast<float>(slices);
            float v = static_cast<float>(i) / static_cast<float>(stacks);

            // Store position
            mVertices.push_back(position.x);
            mVertices.push_back(position.y);
            mVertices.push_back(position.z);

            // Store normal
            mVertices.push_back(normal.x);
            mVertices.push_back(normal.y);
            mVertices.push_back(normal.z);

            // Store texture coordinates
            mVertices.push_back(u);
            mVertices.push_back(v);
        }
    }

    // Generate indices
    for (unsigned int i = 0; i < stacks; ++i) {
        for (unsigned int j = 0; j < slices; ++j) {
            unsigned int first = i * (slices + 1) + j;
            unsigned int second = first + slices + 1;
                
            // First triangle
            mIndices.push_back(first);
            mIndices.push_back(second);
            mIndices.push_back(first + 1);

            // Second triangle
            mIndices.push_back(second);
            mIndices.push_back(second + 1);
            mIndices.push_back(first + 1);
        }
    }
}


