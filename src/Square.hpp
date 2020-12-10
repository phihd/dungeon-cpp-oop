#pragma once
#ifndef SQUARE_HEADER
#define SQUARE_HEADER

#include "Unit.hpp"
#include <vector>
class Square {
public:
	//Constructor:
	explicit Square();
	//IsObstacle(): Return true if a square is an obstacle: wall/river/mountain
	virtual const bool IsObstacle();
	//IsOccupied(): Return true if a square is occupied by either an enemy or ally unit
	virtual const bool IsOccupied(); 
	//clear(): clear any unit occupying the square
	virtual void Clear();
	//get(): get the unit occupying the square. If there is no unit currently occupying, return NULL
	virtual Unit* Get();
	//put: takes a Unit as a parameter, place a unit into the square, return true if the def sucessfully put a unit inside
	virtual bool Put(Unit* unit);
	//Place: takes a vector of item as parameter. Place treasure to Treasure square, return true if place sucessfully
	virtual bool Place(std::vector<Item>* treasure);
	//IsOpened: return true if the treasure in the treasure square is opened
	virtual bool IsOpened();
	//Open: return true if successfully take the treasure:
	virtual std::vector<Item>* Open();
	//Print the treasure list, Treasure square returns "empty treasure" if empty and other returns "Not Treasure" by defaults
	virtual std::string PrintTreasure();
	//Print the unit occupying the square, Treasure square returns "empty square" if empty and other returns "Not Floor" by defaults
	virtual std::string PrintUnit();
	//Print the type of square
	virtual std::string ToString();
};
//Wall are obstacles on the map as well as the outer edges of the map.
class Wall : public Square {
public:
	Wall();
	//IsObstacle returns true by default
	const bool IsObstacle();
	//IsOccupied returns false by default
	const bool IsOccupied();
	//clear() does nothing
	void Clear();
	//get() returns NULL by default
	Unit* Get();
	//put returns false by default
	bool Put(Unit* unit);
	//Place: returns false by default
	bool Place(std::vector<Item>* treasure);
	//IsOpened: return false by default
	bool IsOpened();
	//Open: return false by default
	std::vector<Item>* Open();
	//returns"Not Treasure" by defaults
	std::string PrintTreasure();
	//returns "Not Floor" by defaults
	std::string PrintUnit();
	//return Wall
	std::string ToString();
private:
	Unit* unit_ = NULL;
	std::vector<Item>* treasure_ = NULL;
};
//Floor square makes playable area, unit can be placed on these square
class Floor : public Square {
public:
	Floor();
	//IsObstacle returns false by default
	const bool IsObstacle();
	//IsOccupied
	const bool IsOccupied();
	//clear()
	void Clear();
	//get() 
	Unit* Get();
	//put
	bool Put(Unit* unit);
	//Place: returns false by default
	bool Place(std::vector<Item>* treasure);
	//IsOpened: return false by default
	bool IsOpened();
	//Open: return false by default
	std::vector<Item>* Open();
	//returns"Not Treasure" by defaults
	std::string PrintTreasure();
	//Print the unit occupying the square, Treasure square returns "empty square" if empty
	std::string PrintUnit();
	//return Floor
	std::string ToString();
private:
	Unit* unit_ = NULL;
	std::vector<Item>* treasure_ = NULL;
};
//Treasure square is a square that contains item as treasure. This Square is also counted as an obstacle.
class Treasure : public Square {
public:
	Treasure();
	//IsObstacle returns true by default
	const bool IsObstacle();
	//IsOccupied returns false by default
	const bool IsOccupied();
	//clear() does nothing
	void Clear();
	//get() returns NULL by default
	Unit* Get();
	//put returns false by default
	bool Put(Unit* unit);
	//Place: returns true by default
	bool Place(std::vector<Item>* treasure);
	//IsOpened: return true if the treasure has already been taken
	bool IsOpened();
	//Open: return true if successfully take the treasure:
	std::vector<Item>* Open();
	//return Treasure
	std::string ToString();
	//Print the treasure list, Treasure square returns "empty treasure" if empty
	std::string PrintTreasure();
	//Print the unit occupying the square, Treasure square returns "empty square" if empty and other returns "Not Floor" by defaults
	std::string PrintUnit();
private:
	std::vector<Item>* treasure_ = NULL;
	Unit* unit_ = NULL;
};
#endif