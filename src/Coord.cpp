#include "Coord.hpp"
#include <string>

Coord::Coord(int x, int y) : std::pair<int, int>(x, y), x_(x), y_(y) {}

int Coord::x() const { return x_; }

int Coord::y() const { return y_; }

std::string Coord::ToString() { return "(" + std::to_string(x_) + ", " + std::to_string(y_) + ")"; }

bool operator==(const Coord& a, const Coord& b) {
    return (a.x() == b.x()) && (a.y() == b.y());
}

bool operator!=(const Coord& a, const Coord& b)
{
    return !(a == b);
}


