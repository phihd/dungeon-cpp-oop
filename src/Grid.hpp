#pragma once
#ifndef GRID_HEADER
#define GRID_HEADER
#include "Square.hpp"
#include "Square.cpp"	// Remove if you use visual studio

class Grid {
public:
	Grid(int nrows, int ncols);
	//returns all element of the grid as a 2D matrix
	std::vector<std::vector<Square*>> Contents();
	//returns the size of the grid
	int Size();
	//get the element at a specific coordinate
	Square* Apply(Coord coord);
	//update the element at a specific coordinate
	void Update(Coord coord, Square* square);
	//print width of the Grid
	int Rows();
	//print height of the Grid
	int Cols();
	//returns the grid as string
	std::string ToString();

private:
	int nrows_;
	int ncols_;
	std::vector<std::vector<Square*>> contents_ = 
		std::vector<std::vector<Square*>> (nrows_, std::vector<Square*> (ncols_, new Wall));
};

#endif
