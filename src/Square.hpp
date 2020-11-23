#pragma once
#include "Unit.hpp"
#include "Item.hpp"
#include <vector>
#include <optional>
class Square {
public:
	//Constructor:
	explicit Square(){};
	//IsObstacle(): Return true if a square is an obstacle: wall/river/mountain
	virtual const bool IsObstacle();
	//IsOccupied(): Return true if a square is occupied by either an enemy or ally unit
	virtual const bool IsOccupied();
	//clear(): clear any unit occupying the square
	virtual void Clear();
	//get(): get the unit occupying the square. If there is no unit currently occupying, return NULL
	virtual Unit* Get();
	//put: takes a Unit as a parameter, place a unit into the square, return true if the def sucessfully put a unit inside
	virtual bool Put(Unit unit);
	//Place: takes a vector of item as parameter. Place treasure to Treasure square, return true if place sucessfully
	virtual bool Place(std::vector<Item> treasure);
	//IsOpened: return true if the treasure in the treasure square is opened
	virtual bool IsOpened();
};
//Wall are obstacles on the map as well as the outer edges of the map.
class Wall : public Square {
public:
	Wall() : Square(){};
	//IsObstacle returns true by default
	const bool IsObstacle() { return true; };
	//IsOccupied returns false by default
	const bool IsOccupied() { return false; };
	//clear() does nothing
	void Clear() {};
	//get() returns NULL by default
	Unit* Get() { return unit_; };
	//put returns false by default
	bool Put(Unit* unit) { (void)unit;  return false; };
	//Place: returns false by default
	bool Place(std::vector<Item> treasure) { return false; };
	//IsOpened: return false by default
	bool IsOpened() { return false; };
private:
	Unit* unit_ = NULL;
};
//Floor square makes playable area, unit can be placed on these square
class Floor : public Square {
public:
	Floor() : Square() {};
	//IsObstacle returns false by default
	const bool IsObstacle() { return false; };
	//IsOccupied
	const bool IsOccupied() { return unit_ != NULL; };
	//clear()
	void Clear() { unit_ = NULL; };
	//get() 
	Unit* Get() { return unit_; };
	//put
	bool Put(Unit* unit) {
		if (!IsOccupied) {
			unit_ = unit;
			return true;
		}
		else {
			return false;
		}
	};
	//Place: returns false by default
	bool Place(std::vector<Item> treasure) { return false; };
	//IsOpened: return false by default
	bool IsOpened() { return false; };
private:
	Unit* unit_ = NULL;
};
//Treasure square is a square that contains item as treasure. This Square is also counted as an obstacle.
class Treasure : public Square {
public:
	Treasure() : Square() {};
	//IsObstacle returns true by default
	const bool IsObstacle() { return true; };
	//IsOccupied returns false by default
	const bool IsOccupied() { return false; };
	//clear() does nothing
	void Clear() {};
	//get() returns NULL by default
	Unit* Get() { return unit_; };
	//put returns false by default
	bool Put(Unit* unit) { (void)unit;  return false; };
	//Place: returns true by default
	bool Place(std::vector<Item*>* treasure) { treasure_ = treasure; return true; };
	//IsOpened: return true if the treasure has already been taken
	bool IsOpened() { return treasure_ == NULL; };
private:
	std::vector<Item*>* treasure_ = NULL;
	Unit* unit_ = NULL;
};
