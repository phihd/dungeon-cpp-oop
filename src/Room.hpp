#pragma once
#include "Grid.hpp"
#include "Item.hpp"
class Room : public Grid {
public:
	Room(int nrows, int ncols, std::vector<Unit> enemies, std::vector<Unit> allies, std::vector<Item> treasures) : Grid(nrows+2, ncols +2){
		for (int x = 0; x <= nrows + 2; i++) {
			for (int y = 0; y <= ncols + 2; j++) {
				if (x > 0 && x < (nrows + 1) && y > 0 && y < (ncols + 1))
					this->Update(new Coord(x, y), new Floor);
				else
					this->Update(new Coord(x, y), new Wall);
			}
		}
	}

	//Add wall to a specific coordinate. This function helps design each room. Some sort of random algorithm 
	//can be implemented along with this function to randomize the rooms.
	void AddWall(Coord coord) {this->Update(coord, new Wall)};
	//Add unit to a specific coordinate. This function helps arrange the units on the grid for the first turn
	//and used to move the units around. Returns true if the action succeed
	bool AddUnit(Coord coord, Unit unit) {
		Square current = this->Apply(coord);
		bool result = current.Put(unit);
		return result;
	};

private:
	std::vector<Unit> enemies_ = enemies;
	std::vector<Unit> allies_ = allies;
};


