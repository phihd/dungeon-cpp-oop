#pragma once
#include "Square.hpp"
#include <vector>
class Coord : std::pair<int, int> {
public:
	Coord(int x, int y) : std::pair<int, int>(x, y){}

	int x() { return x_; };

	int y() { return y_; };
private:
	int x_ = this->first;
	int y_ = this->second;
};
class Grid {
public:
	Grid(int nrows, int ncols) : nrows_(nrows), ncols_(ncols) {}
	//returns all element of the grid as a 2D matrix
	std::vector<std::vector<Square*>> Contents() { return contents_; };
	//returns the size of the grid
	int Size() { return nrows_ * ncols_; };
	//get the element at a specific coordinate
	Square* Apply(Coord coord) { return contents_[coord.x()][coord.y()]; };
	//update the element at a specific coordinate
	void Update(Coord coord, Square* square) { contents_[coord.x()][coord.y()] = square; };
	//print width of the Grid
	int Rows() { return nrows_; };
	//print height of the Grid
	int Cols() { return ncols_; };
	//returns the grid as string
	std::string ToString() {
		std::string result;
		for (int y = 0; y < ncols_; y++) {
			for (int x = 0; x < nrows_; x++) {
				Coord coord = Coord(x, y);
				Square* square = this->Apply(coord);
				if (square->ToString() == "Wall")
					result += "#";
				else if (square->ToString() == "Floor")
					result += ".";
				else if (square->ToString() == "Treasure") {
					if (square->IsOpened())
						result += "0";
					else
						result += "1";
				}
				else
					continue;
			}
			result += "\n";
		}
		return result;
	};
private:
	int nrows_;
	int ncols_;
	std::vector<std::vector<Square*>> contents_ = 
		std::vector<std::vector<Square*>> (nrows_, std::vector<Square*> (ncols_, new Wall));
};
