#pragma once
#include "Grid.hpp"
#include "Item.hpp"
#include "Player.hpp"
#include <typeinfo>
class Room {
public:
	explicit Room() {};
};
/*
class Rest : public Room {
public:
	Rest(std::vector<Item> stock) : Room(), stock_(stock) {};

	//The player can buy items at the shop if there is enough money. Returns true if the action succeeded	
	bool Buy(Player player, Item item, int quantity) { 
		if (player.GetGold() >= item.GetPrice() * quantity) {
			player.Buy(item, quantity);
			return true;
		}
		else
			return false;	 
	};
	//The player can buy items at the shop if there are enough items to sell. Returns true if the action succeeded
	bool Sell(Player player, Item item, int quantity) { 
		std::map<Item, int> inventory = player.GetInventory();
		if (inventory.find(item) == inventory.end())
			return false;
		else {
			if (inventory[item] >= quantity) {
				player.Sell(item, quantity);
				return true;
			}
			else
				return false;
		}
		 
	};
	void Heal(Player player) { player.Rest(); };
private:
	std::vector<Item> stock_;
};
*/
class Battlefield : public Grid, public Room {
public:
	Battlefield(int nrows, int ncols, std::vector<Unit*> enemies, std::vector<Unit*> allies,
		std::vector<Item>* treasures, std::vector<Coord> spawn) : 
		Grid(nrows, ncols), Room(), enemies_(enemies), allies_(allies), treasures_(treasures), spawn_(spawn) {
		for (int x = 0; x < this->Rows(); x++) {
			for (int y = 0; y < this->Cols(); y++) {
				if (x > 0 && x < nrows - 1 && y > 0 && y < ncols - 1)
					this->Update(Coord(x, y), new Floor);
				else
					this->Update(Coord(x, y), new Wall);
			}
		}
	};

	//Add wall to a specific coordinate. This function helps design each room. Some sort of random algorithm 
	//can be implemented along with this function to randomize the rooms.
	void AddWall(Coord coord) { this->Update(coord, new Wall); };
	//Add Treasure square to a specific coordinate.
	void AddTreasure(Coord coord) {this->Update(coord, new Treasure); };
	//Put Treasure put the treasures from the room's attribute to the Treasure square on the map. Return true if the action is successful.
	bool PutTreasure(Coord coord) {
		Square* current = this->Apply(coord);
		if (current->ToString() != "Treasure") {
			return false;
		}
		else {
			bool result = current->Place(treasures_);
			return result;
		}
	};
	//Add unit to a specific coordinate. This function helps arrange the units on the grid for the first turn
	//and used to move the units around. Returns true if the action succeed
	bool AddUnit(Coord coord, Unit unit) {
		Square* current = this->Apply(coord);
		bool result = current->Put(unit);
		return result;
	};

	//FromString creates a Room from a vector of string. Returns true if the action is successful.
	bool FromString(std::vector<string> room) {
		for (unsigned int y = 0; y < room.size(); y++) {
			string row = room[y];
			for (unsigned int x = 0; x < row.length(); x++) {
				Coord coord = Coord(x+1, y+1);
				char c = row[x];
				if (c == '#') {
					this->AddWall(coord);
				}
				else if (c == '.') {
					continue;
				}
				else if (c == '0' || c == '1') {
					this->AddTreasure(coord);
					if (c == '1') {
						bool result = this->PutTreasure(coord);
						if (!result) {
							return false;
						}
					}
				}
				else {
					return false;
				}
			}
		}
		return true;
	}

	//ToString saves the room as a vector of string.
	std::vector<string> ToString() {
		std::vector<string> result;
		for (int y = 0; y < this->Cols(); y++) {
			string row;
			for (int x = 0; x < this->Rows(); x++) {
				Coord coord = Coord(x, y);
				Square* square = this->Apply(coord);
				if (square->ToString() == "Wall")
					row += "#";
				else if (square->ToString() == "Floor")
					row += ".";
				else if (square->ToString() == "Treasure") {
					if (square->IsOpened())
						row += "0";
					else
						row += "1";
				}
				else
					continue;
			}
			result.push_back(row);
		}
		return result;
	}

private:
	std::vector<Coord> spawn_;
	std::vector<Unit*> enemies_;
	std::vector<Unit*> allies_;
	std::vector<Item>* treasures_;
};


