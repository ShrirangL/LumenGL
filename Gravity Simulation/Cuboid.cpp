#include "Cuboid.h"
#include <array>

Cuboid::Cuboid(float width, float height, float depth)
	: IDrawable(), mWidth(width), mHeight(height), mDepth(depth)
{
	IDrawable::build();
}

Cuboid::Cuboid(const Point& centre, float width, float height, float depth)
	: IDrawable(centre), mWidth(width), mHeight(height), mDepth(depth)
{
	IDrawable::build();
}

Cuboid::Cuboid(float x, float y, float z, float width, float height, float depth)
	: IDrawable(x,y,z), mWidth(width), mHeight(height), mDepth(depth)
{
	IDrawable::build();
}

//void Cuboid::generateVerticesAndIndices()
//{
//	mVertices.clear();
//	mIndices.clear();
//
//	float w = mWidth / 2.0f;
//	float h = mHeight / 2.0f;
//	float d = mDepth / 2.0f;
//
//	// 8 corner vertices (in world space)
//	std::vector<glm::vec3> corners = {
//		{mCentre.x - w, mCentre.y - h, mCentre.z - d}, // 0: left-bottom-back
//		{mCentre.x + w, mCentre.y - h, mCentre.z - d}, // 1: right-bottom-back
//		{mCentre.x + w, mCentre.y + h, mCentre.z - d}, // 2: right-top-back
//		{mCentre.x - w, mCentre.y + h, mCentre.z - d}, // 3: left-top-back
//		{mCentre.x - w, mCentre.y - h, mCentre.z + d}, // 4: left-bottom-front
//		{mCentre.x + w, mCentre.y - h, mCentre.z + d}, // 5: right-bottom-front
//		{mCentre.x + w, mCentre.y + h, mCentre.z + d}, // 6: right-top-front
//		{mCentre.x - w, mCentre.y + h, mCentre.z + d}  // 7: left-top-front
//	};
//
//	// List of triangle indices (2 per face)
//	std::vector<std::array<int, 3>> triangles = {
//		// Back face
//		{0, 1, 2}, {2, 3, 0},
//		// Front face
//		{4, 6, 5}, {6, 4, 7},
//		// Left face
//		{0, 3, 7}, {7, 4, 0},
//		// Right face
//		{1, 5, 6}, {6, 2, 1},
//		// Bottom face
//		{0, 4, 5}, {5, 1, 0},
//		// Top face
//		{3, 2, 6}, {6, 7, 3}
//	};
//
//	// For each triangle: compute face normal and store 3 vertices (position + normal)
//	for (const auto& tri : triangles)
//	{
//		glm::vec3 v0 = corners[tri[0]];
//		glm::vec3 v1 = corners[tri[1]];
//		glm::vec3 v2 = corners[tri[2]];
//
//		glm::vec3 edge1 = v1 - v0;
//		glm::vec3 edge2 = v2 - v0;
//		glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));
//
//		// Append each vertex with its normal (per-face flat shading)
//		auto addVertex = [&](const glm::vec3& v) {
//			mVertices.push_back(v.x);
//			mVertices.push_back(v.y);
//			mVertices.push_back(v.z);
//			mVertices.push_back(normal.x);
//			mVertices.push_back(normal.y);
//			mVertices.push_back(normal.z);
//			};
//
//		addVertex(v0);
//		addVertex(v1);
//		addVertex(v2);
//	}
//
//	// Optional: You can remove mIndices if using glDrawArrays
//	// If using glDrawElements, fill mIndices like this:
//	for (int i = 0; i < mVertices.size() / 6; ++i)
//		mIndices.push_back(i);
//}

void Cuboid::setShapeType()
{
	mShapeType = ShapeType::Shape3D;
}

void Cuboid::generateVerticesAndIndices()
{
    mVertices.clear();
    mIndices.clear();

    float w = mWidth / 2.0f;
    float h = mHeight / 2.0f;
    float d = mDepth / 2.0f;

    // 8 corners
    std::vector<glm::vec3> corners = {
        {mCentre.x - w, mCentre.y - h, mCentre.z - d}, // 0: left-bottom-back
        {mCentre.x + w, mCentre.y - h, mCentre.z - d}, // 1: right-bottom-back
        {mCentre.x + w, mCentre.y + h, mCentre.z - d}, // 2: right-top-back
        {mCentre.x - w, mCentre.y + h, mCentre.z - d}, // 3: left-top-back
        {mCentre.x - w, mCentre.y - h, mCentre.z + d}, // 4: left-bottom-front
        {mCentre.x + w, mCentre.y - h, mCentre.z + d}, // 5: right-bottom-front
        {mCentre.x + w, mCentre.y + h, mCentre.z + d}, // 6: right-top-front
        {mCentre.x - w, mCentre.y + h, mCentre.z + d}  // 7: left-top-front
    };

    // For each face: {triangle indices, uv for each corner}
    struct Face {
        std::array<int, 4> idx;
        glm::vec3 normal;
        std::array<std::pair<float, float>, 4> uv;
    };

    std::vector<Face> faces = {
        // Back face (z-)
        {{0, 1, 2, 3}, {0, 0, -1}, {{ {0,0}, {1,0}, {1,1}, {0,1} }}},
        // Front face (z+)
        {{4, 5, 6, 7}, {0, 0, 1},  {{ {0,0}, {1,0}, {1,1}, {0,1} }}},
        // Left face (x-)
        {{0, 3, 7, 4}, {-1, 0, 0}, {{ {0,0}, {1,0}, {1,1}, {0,1} }}},
        // Right face (x+)
        {{1, 5, 6, 2}, {1, 0, 0},  {{ {0,0}, {1,0}, {1,1}, {0,1} }}},
        // Bottom face (y-)
        {{0, 1, 5, 4}, {0, -1, 0}, {{ {0,0}, {1,0}, {1,1}, {0,1} }}},
        // Top face (y+)
        {{3, 2, 6, 7}, {0, 1, 0},  {{ {0,0}, {1,0}, {1,1}, {0,1} }}}
    };

    int vertIndex = 0;
    for (const auto& face : faces) {
        // Two triangles per face: (0,1,2) and (2,3,0)
        for (int t = 0; t < 2; ++t) {
            int i0 = t == 0 ? 0 : 2;
            int i1 = t == 0 ? 1 : 3;
            int i2 = t == 0 ? 2 : 0;
            for (int i : {i0, i1, i2}) {
                const glm::vec3& v = corners[face.idx[i]];
                mVertices.push_back(v.x);
                mVertices.push_back(v.y);
                mVertices.push_back(v.z);
                mVertices.push_back(face.normal.x);
                mVertices.push_back(face.normal.y);
                mVertices.push_back(face.normal.z);
                mVertices.push_back(face.uv[i].first);
                mVertices.push_back(face.uv[i].second);
                mIndices.push_back(vertIndex++);
            }
        }
    }
}

