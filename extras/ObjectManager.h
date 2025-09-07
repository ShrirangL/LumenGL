#pragma once

#include <vector>
#include <memory>
#include "IDrawable.h"
#include "Point.h"

class ObjectManager
{
    std::vector<std::unique_ptr<IDrawable>> mObjects;
public:
    void createLine(const Point& start, const Point& end);
    void createTriangle(const Point& p1, const Point& p2, const Point& p3);
    void createRectangle(const Point& bottomLeft, const Point& topRight);
    void createCircle(const Point& centre, float radius);
    void createCuboid(const Point& centre, float width, float height, float depth);
    void createCylinder(const Point& bottomCentre, const Point& topCentre, float radius);
    void createSphere(const Point& centre, float radius);

    const std::vector<std::unique_ptr<IDrawable>>& getShapes() const;
    void drawShapes() const;
};
