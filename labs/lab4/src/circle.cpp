#include "circle.hpp"
#include <stdexcept>

using namespace std;

static const double PI = 3.14159265358979323846;

Circle::Circle() : center(), radius(0) {}

Circle::Circle(const Point &center, double radius) : center(center), radius(radius) {
    if (radius < 0){
        throw invalid_argument("Circle: negative radius");
    }
}

Circle::Circle(double x, double y, double radius) : center(x, y), radius(radius) {
    if (radius < 0){
        throw invalid_argument("Circle: negative radius");
    }
}

const Point& Circle::get_center() const {
    return center;
}

double Circle::get_radius() const {
    return radius;
}

double Circle::area() const {
    return PI * radius * radius;
}

bool Circle::operator==(const Circle &other) const {
    return center == other.center && radius == other.radius;
}

bool Circle::operator!=(const Circle &other) const {
    return !(*this == other);
}

ostream& operator<<(ostream &os, const Circle &c){
    os << "Circle: center " << c.get_center() << ", radius " << c.get_radius();
    return os;
}
