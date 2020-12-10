#pragma once
#ifndef ROOM_HEADER
#define ROOM_HEADER

#include "Grid.hpp"
#include "Grid.cpp"		// This is for VSCode, remove if you use visual studio

class Room {
public:
	explicit Room();

	virtual string type();
};

/*Rest stop between the rooms*/

class Rest : public Room {
public:
	Rest(std::vector<Item>* stock);

	std::vector<Item>* Stock();

	string type();
	//import items to stock
	void Import(std::vector<Item> items);
private:
	std::vector<Item>* stock_;
};

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
	//Check if the unit can move to the destination
	//bool Movable(Coord coord, Unit* unit);
	//MoveUnit move a unit from it's original location and bring it to the destination coordinate. Returns true if action succeed
	bool MoveUnit(Coord coord, Unit* unit);
	//FromString creates a Room from a vector of string. Returns true if the action is successful.
	std::string FromString(std::vector<string> room);
	//ToString saves the room as a vector of string. #: wall, .:Room, 1-n: Ally or Enemy, no separating which is which
	//o: opened Treasure, c:closed Treasure.
	std::vector<string> ToString();
	//ToInt saves the room as a vector of vector of int. 1-5: Allies, -1 to -n: Enemies, 0: Floor, 6:Wall, 7: opened Treasure,
	//8: closed Treasure. This is feed forward to GUI.
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
	//Return outcome of a battle between to units. Returns true if 2 units are able to attack each other and if they have different type
	bool Outcome(Unit* attacker, Unit* defender);
	//Add Ally units to Room
	bool AllyArrive(std::vector<Ally*> army);
	//Add Enemy units to Room
	bool EnemyArrive(std::vector<Enemy*> army);

	string type();
	
	std::vector<Coord> BFS(Coord coord, int range);

	std::vector<Coord> BFS_Attack(Coord coord, int range);
private:
	std::vector<Coord> ally_spawn_ = {};
	std::vector<Coord> enemy_spawn_ = {};
	std::vector<Enemy*> enemies_;
	std::vector<Ally*> allies_;
	std::vector<Item>* treasures_;
};
#endif

