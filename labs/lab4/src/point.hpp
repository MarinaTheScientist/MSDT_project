#pragma once
#include <iostream>

class Point
{
private:
    double x;
    double y;

public:
    Point(double x = 0, double y = 0);

    double get_x() const;
    double get_y() const;
    void set(double x, double y);

    bool operator==(const Point &other) const;
    bool operator!=(const Point &other) const;
};

std::ostream& operator<<(std::ostream &os, const Point &p);
