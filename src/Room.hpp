#pragma once
#include "Grid.hpp"
#include "Item.hpp"
class Room {
public:
	Room(int nrows, int ncols, vector<Unit> enemies, vector<Unit> allies, vector<Item> treasures) : Grid(nrows+2, ncols +2){
		for (int x = 0; x <= nrows + 2; i++) {
			for (int y = 0; y <= ncols + 2; j++) {
				if (x > 0 && x < (nrows + 1) && y > 0 && y < (ncols + 1))
					Floor;
				else
					Wall;
			}
		}
	}
	Room


private:
};


