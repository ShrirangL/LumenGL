#include "Cylinder.h"

Cylinder::Cylinder(float height, float radius)
	: IDrawable(), topCentre(0.0, height / 2, 0.0), bottomCentre(0.0, -height / 2, 0.0), height(height), radius(radius)
{
	IDrawable::build();
}

Cylinder::Cylinder(const Point& point, float height, float radius)
	: IDrawable(point.x, point.y+height/2, point.z), topCentre(point.x, point.y+height, point.z), bottomCentre(point), height(height), radius(radius)
{
	IDrawable::build();
}

Cylinder::Cylinder(const Point& tCentre, const Point& bCentre, float radius)
	: IDrawable((tCentre.x + bCentre.x)/2, (tCentre.y + bCentre.y) / 2, (tCentre.z + bCentre.z) / 2), topCentre(tCentre), bottomCentre(bCentre), height(bCentre.distance(tCentre)), radius(radius)
{
	IDrawable::build();
}

void Cylinder::setShapeType()
{
	IDrawable::setShapeType3D();
}

void Cylinder::generateVerticesAndIndices()
{
    const int segments = 32;
    const float angleStep = 2.0f * PI / segments;

    mVertices.clear();
    mIndices.clear();

    Point center = mCentre;
    float halfHeight = height / 2.0f;

    Point topCenter(center.x, center.y + halfHeight, center.z);
    Point bottomCenter(center.x, center.y - halfHeight, center.z);

    // --- Add cap center vertices (with normal and UV) ---
    // Top cap center: normal up, UV center
    mVertices.insert(mVertices.end(), { topCenter.x, topCenter.y, topCenter.z, 0, 1, 0, 0.5f, 0.5f });
    // Bottom cap center: normal down, UV center
    mVertices.insert(mVertices.end(), { bottomCenter.x, bottomCenter.y, bottomCenter.z, 0, -1, 0, 0.5f, 0.5f });

    // --- Add ring vertices for caps and sides ---
    // We'll keep track of indices for each set
    std::vector<unsigned int> topCapRingIndices, bottomCapRingIndices, topSideRingIndices, bottomSideRingIndices;

    for (int i = 0; i <= segments; ++i) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float z = radius * sin(angle);

        // --- Cap UVs: polar mapping ---
        float u_cap = 0.5f + 0.5f * cos(angle);
        float v_cap = 0.5f + 0.5f * sin(angle);

        // --- Side UVs: cylindrical mapping ---
        float u_side = static_cast<float>(i) / segments;

        // Top cap ring vertex (normal up)
        mVertices.insert(mVertices.end(), { center.x + x, topCenter.y, center.z + z, 0, 1, 0, u_cap, v_cap });
        topCapRingIndices.push_back(static_cast<unsigned int>(mVertices.size() / 8 - 1));

        // Bottom cap ring vertex (normal down)
        mVertices.insert(mVertices.end(), { center.x + x, bottomCenter.y, center.z + z, 0, -1, 0, u_cap, v_cap });
        bottomCapRingIndices.push_back(static_cast<unsigned int>(mVertices.size() / 8 - 1));

        // Top side ring vertex (normal out)
        mVertices.insert(mVertices.end(), { center.x + x, topCenter.y, center.z + z, x, 0, z, u_side, 1.0f });
        topSideRingIndices.push_back(static_cast<unsigned int>(mVertices.size() / 8 - 1));

        // Bottom side ring vertex (normal out)
        mVertices.insert(mVertices.end(), { center.x + x, bottomCenter.y, center.z + z, x, 0, z, u_side, 0.0f });
        bottomSideRingIndices.push_back(static_cast<unsigned int>(mVertices.size() / 8 - 1));
    }

    // --- Indices for top cap triangles ---
    unsigned int topCenterIdx = 0;
    for (int i = 0; i < segments; ++i) {
        mIndices.push_back(topCenterIdx);
        mIndices.push_back(topCapRingIndices[i]);
        mIndices.push_back(topCapRingIndices[i + 1]);
    }

    // --- Indices for bottom cap triangles ---
    unsigned int bottomCenterIdx = 1;
    for (int i = 0; i < segments; ++i) {
        mIndices.push_back(bottomCenterIdx);
        mIndices.push_back(bottomCapRingIndices[i + 1]);
        mIndices.push_back(bottomCapRingIndices[i]);
    }

    // --- Indices for side quads (as two triangles per segment) ---
    for (int i = 0; i < segments; ++i) {
        unsigned int top1 = topSideRingIndices[i];
        unsigned int bottom1 = bottomSideRingIndices[i];
        unsigned int top2 = topSideRingIndices[i + 1];
        unsigned int bottom2 = bottomSideRingIndices[i + 1];

        // Triangle 1
        mIndices.push_back(top1);
        mIndices.push_back(bottom1);
        mIndices.push_back(top2);

        // Triangle 2
        mIndices.push_back(top2);
        mIndices.push_back(bottom1);
        mIndices.push_back(bottom2);
    }
}

