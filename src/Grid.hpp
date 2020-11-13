#pragma once
#include "Square.hpp"
#include <vector>
class Coord : std::pair<int, int> {
public:
	Coord(int x, int y) : std::pair<int, int>(x, y){}

	int x() { return x; };

	int y() { return y; };
};
class Grid {
public:
	Grid(int nrows, int ncols){}
	//returns all element of the grid as a 2D matrix
	std::vector<std::vector<Square>> Contents() { return contents_; };
	//returns the size of the grid
	int Size() { return nrows_ * ncols_; };
	//get the element at a specific coordinate
	Square Apply(Coord coord) { return contents_[coord.x][coord.y]; };
	//update the element at a specific coordinate
	void Update(Coord coord, Square square) { contents_[coord.x][coord.y] = square; };
private:
	int nrows_ = nrows;
	int ncols_ = ncols;
	std::vector<std::vector<Square>> contents_;
};
