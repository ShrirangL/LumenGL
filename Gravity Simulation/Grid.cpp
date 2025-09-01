#include "Grid.h"

Grid::Grid(int lines, float spacing)
    : IDrawable(), mLinesCount(lines), mSpacing(spacing)
{
    build();
}

Grid::Grid(int lines, float spacing, const Point& centre)
    : IDrawable(centre), mLinesCount(lines), mSpacing(spacing)
{
    build();
}

void Grid::setLayout()
{
    IDrawable::setVBLLayout3Floats();
}

void Grid::setShapeType()
{
	IDrawable::setShapeType2D();
}

void Grid::generateVerticesAndIndices()
{
    mVertices.clear();
    mIndices.clear();

    int half = mLinesCount / 2;
    unsigned int index = 0;

    for (int i = -half; i <= half; ++i)
    {
        float coord = i * mSpacing;

        // Lines parallel to Z axis (constant X)
        mVertices.push_back(coord); mVertices.push_back(0.0f); mVertices.push_back(-half * mSpacing); // start
        mVertices.push_back(coord); mVertices.push_back(0.0f); mVertices.push_back(half * mSpacing);  // end

        mIndices.push_back(index++);
        mIndices.push_back(index++);

        // Lines parallel to X axis (constant Z)
        mVertices.push_back(-half * mSpacing); mVertices.push_back(0.0f); mVertices.push_back(coord); // start
        mVertices.push_back(half * mSpacing);  mVertices.push_back(0.0f); mVertices.push_back(coord); // end

        mIndices.push_back(index++);
        mIndices.push_back(index++);
    }
}
