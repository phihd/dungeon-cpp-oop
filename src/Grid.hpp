#pragma once
#include "Square.hpp"
#include <vector>
#include <iostream>
class Coord {
public:
	Coord(int x, int y) : std::pair<int, int>(x, y){}

	int x() { return x; };

	int y() { return y; };
};
class Grid {
public:
	Grid(int nrows, int ncols){}

	std::vector<std::vector<Square>> Contents() { return contents_; };

	int Size() { return nrows_ * ncols_; };

	Square Apply(Coord coord) {contents[coord.x][coord.y]};

	void Update(Coord coord, Square square) { contents_[coord.x][coord.y] = square; }
private:
	int nrows_ = nrows;
	int ncols_ = ncols;
	std::vector<std::vector<Square>> contents_;
};
