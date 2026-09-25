#pragma once
#include <iostream>
#include "point.hpp"

class Circle
{
private:
    Point center;
    double radius;

public:
    Circle();
    Circle(const Point &center, double radius);
    Circle(double x, double y, double radius);

    const Point& get_center() const;
    double get_radius() const;
    double area() const;

    bool operator==(const Circle &other) const;
    bool operator!=(const Circle &other) const;
};

std::ostream& operator<<(std::ostream &os, const Circle &c);
