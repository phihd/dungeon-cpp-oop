#include "Coord.hpp"
#include <string>

Coord::Coord(int x, int y) : std::pair<int, int>(x, y), x_(x), y_(y) {}

int Coord::x() { return x_; }

int Coord::y() { return y_; }

std::string Coord::ToString() { return "(" + std::to_string(x_) + ", " + std::to_string(y_) + ")"; }