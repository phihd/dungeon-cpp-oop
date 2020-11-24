#include "World.hpp"
#include <iostream>
int main() 
{
	Grid grid(10, 10);
    std::vector<std::vector<Square*>> test = grid.Contents();
	std::string result = grid.ToString();
	Battlefield room1(10, 10, {}, {}, {}, {});
	std::vector<std::string> result2 = room1.ToString();
	/*
	for (int y = 0; y < grid.Cols(); y++) {
		for (int x = 0; x < grid.Rows(); x++) {
			Coord coord = Coord(x, y);
			std::cout << "(" << coord.x() << ", " << coord.y() << ")";
			Square* square = grid.Apply(coord);
			std::cout << test[x][y]->ToString() << " | ";
			if (typeid(square).name() == "class Wall")
				result += "#";
			else if (typeid(square).name() == "class Floor")
				result += ".";
			else if (typeid(square).name() == "class Treasure") {
				if (square->IsOpened())
					result += "0";
				else
					result += "1";
			}
			else
				continue;
		}
		//result += "\n";
		std::cout << "\n";
	}
	*/
	std::cout << result2.size();
	/*
	for (unsigned int i = 0; i < result2.size(); i++) {
		std::cout << i << std::endl;
	}
	*/
	return 0;
}