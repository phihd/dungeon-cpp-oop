#pragma once
#ifndef ROOM_HEADER
#define ROOM_HEADER

#include "Grid.hpp"
#include "Item.hpp"
#include "Player.hpp"
class Room {
public:
	explicit Room();
};

/*Rest stop between the rooms*/
/*
class Rest : public Room {
public:
	Rest(std::vector<Item> stock) : Room(), stock_(stock) {};

	//The player can buy items at the shop if there is enough money. Returns true if the action succeeded	
	bool Buy(Player player, Item item, int quantity) { 
		if (player.GetGold() >= item.GetPrice() * quantity) {
			player.Buy(item, quantity, stock_);
			return true;
		}
		else
			return false;	 
	};
	//The player can buy items at the shop if there are enough items to sell. Returns true if the action succeeded
	bool Sell(Player player, Item item, int quantity) { 
		std::map<Item, int> inventory = player.GetInv entory();
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

/*Playable Area*/
class Battlefield : public Grid, public Room {
public:
	Battlefield(int nrows, int ncols, std::vector<Unit*> enemies, std::vector<Unit*> allies,
		std::vector<Item>* treasures, std::vector<Coord> spawn);

	//Add wall to a specific coordinate. This function helps design each room. Some sort of random algorithm 
	//can be implemented along with this function to randomize the rooms.
	void AddWall(Coord coord);
	//Add Treasure square to a specific coordinate.
	void AddTreasure(Coord coord);
	//Put Treasure put the treasures from the room's attribute to the Treasure square on the map. Return true if the action is successful.
	std::string PutTreasure(Coord coord);
	//Add unit to a specific coordinate. This function helps arrange the units on the grid for the first turn
	//and used to move the units around. Returns true if the action succeed
	bool AddUnit(Coord coord, Unit unit);

	//FromString creates a Room from a vector of string. Returns true if the action is successful.
	std::string FromString(std::vector<string> room);

	//ToString saves the room as a vector of string.
	std::vector<string> ToString();

private:
	std::vector<Coord> spawn_;
	std::vector<Unit*> enemies_;
	std::vector<Unit*> allies_;
	std::vector<Item>* treasures_;
};
#endif

