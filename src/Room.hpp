#pragma once
#ifndef ROOM_HEADER
#define ROOM_HEADER

#include "Grid.hpp"
#include "Grid.cpp"		// This is for VSCode, remove if you use visual studio
//#include "Player.hpp"

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
	Battlefield(int nrows, int ncols, std::vector<Enemy*> enemies, std::vector<Ally*> allies, std::vector<Item>* treasures);

	//Add wall to a specific coordinate. This function helps design each room. Some sort of random algorithm 
	//can be implemented along with this function to randomize the rooms.
	void AddWall(Coord coord);
	//Add Treasure square to a specific coordinate.
	void AddTreasure(Coord coord);
	//Put Treasure put the treasures from the room's attribute to the Treasure square on the map. Return true if the action is successful.
	std::string PutTreasure(Coord coord);
	//Add unit to a specific coordinate. This function helps arrange the units on the grid for the first turn
	//and used to move the units around. Returns true if the action succeed
	bool AddUnit(Coord coord, Unit* unit);
	//RemoveUnit removes a unit from a specific Coordinate. Returns true if action succeed
	bool RemoveUnit(Coord coord, Unit* unit);
	//MoveUnit move a unit from it's original location and bring it to the destination coordinate. Returns true if action succeed
	bool MoveUnit(Coord coord, Unit* unit);
	//FromString creates a Room from a vector of string. Returns true if the action is successful.
	std::string FromString(std::vector<string> room);
	//ToString saves the room as a vector of string.
	std::vector<string> ToString();
	//ToInt saves the room as a vector of vector of int.
	std::vector<std::vector<int>> ToInt();
	//Set spawnpoints of allies
	void SetAllySpawn(std::vector<Coord> spawns);
	//Set spawnpoints of enemies
	void SetEnemySpawn(std::vector<Coord> spawns);
	//Return ally spawn coordinate
	std::vector<Coord> AllySpawn();
	//Return enemy spawn coordinate
	std::vector<Coord> EnemySpawn();
	//Spawn in allies from spawn coordinates returns true if action is successful
	bool SpawnAlly();
	//Spawn in Enemies randomly if enemy_spawn is not NULL, returns true if action is successful
	bool SpawnEnemy();
	//Return coordinate of the treasure chest
	Coord TreasureCoord();
	//Open treasure returns true if the action is successful.
	bool OpenTreasure();
	//Enemies returns list of alive enemy in the room
	std::vector<Enemy*> Enemies();
	//Allies returns list of alive ally in the room
	std::vector<Ally*> Allies();
	//Treasure returns list of unopened treasure
	std::vector<Item>* RemainingTreasure();
	//HasTreasure returns true if there is treasure remaining in the room and is unopened
	bool HasTreasure();
	//HasEnemies returns true if there is enemy remaining in the room
	bool HasEnemies();
	//IsClear returns true if the objective of the room is completed
	bool IsClear();
	

private:
	std::vector<Coord> ally_spawn_ = {};
	std::vector<Coord> enemy_spawn_ = {};
	std::vector<Enemy*> enemies_;
	std::vector<Ally*> allies_;
	std::vector<Item>* treasures_;
};
#endif

