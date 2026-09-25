#include "point.hpp"

using namespace std;

Point::Point(double x, double y) : x(x), y(y) {}

double Point::get_x() const {
    return x;
}

double Point::get_y() const {
    return y;
}

void Point::set(double x, double y){
    this->x = x;
    this->y = y;
}

bool Point::operator==(const Point &other) const {
    return x == other.x && y == other.y;
}

bool Point::operator!=(const Point &other) const {
    return !(*this == other);
}

ostream& operator<<(ostream &os, const Point &p){
    os << "(" << p.get_x() << ", " << p.get_y() << ")";
    return os;
}
