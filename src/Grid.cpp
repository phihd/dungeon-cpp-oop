#include "Grid.hpp"

/**************************************************************************************************************/

Grid::Grid(int nrows, int ncols) : nrows_(nrows), ncols_(ncols) {}

std::vector<std::vector<Square*>> Grid::Contents() { return contents_; }

int Grid::Size() { return nrows_ * ncols_; }

Square* Grid::Apply(Coord coord) { return contents_[coord.x()][coord.y()]; }

void Grid::Update(Coord coord, Square* square) { contents_[coord.x()][coord.y()] = square; }

int Grid::Rows() { return nrows_; }

int Grid::Cols() { return ncols_; }

std::string Grid::ToString() {
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
}

