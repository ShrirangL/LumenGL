#pragma once

#pragma once
#include "IDrawable.h"

class Grid : public IDrawable
{
    unsigned int mLinesCount;
    float mSpacing;
public:
    Grid(int lines = 20, float spacing = 1.0f);
    Grid(int lines, float spacing, const Point& centre);

    void setLayout() override;
    void setShapeType() override;
    void generateVerticesAndIndices() override;
};
