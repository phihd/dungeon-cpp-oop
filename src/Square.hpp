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
	virtual const bool IsObstacle() { return false; };
	//IsOccupied(): Return true if a square is occupied by either an enemy or ally unit
	virtual const bool IsOccupied() { return false; };
	//clear(): clear any unit occupying the square
	virtual void Clear() {};
	//get(): get the unit occupying the square. If there is no unit currently occupying, return NULL
	virtual Unit* Get() { return NULL; };
	//put: takes a Unit as a parameter, place a unit into the square, return true if the def sucessfully put a unit inside
	virtual bool Put(Unit unit) { return false; };
	//Place: takes a vector of item as parameter. Place treasure to Treasure square, return true if place sucessfully
	virtual bool Place(std::vector<Item>* treasure) { return false; };
	//IsOpened: return true if the treasure in the treasure square is opened
	virtual bool IsOpened() { return false; };
	//Open: return true if successfully take the treasure:
	bool Open() { return false; };
	//Print the treasure list, Treasure square returns "empty treasure" if empty and other returns "Not Treasure" by defaults
	virtual std::string PrintTreasure() { return ""; };
	//Print the unit occupying the square, Treasure square returns "empty square" if empty and other returns "Not Floor" by defaults
	virtual std::string PrintUnit() { return ""; };
	//Print the type of square
	virtual std::string ToString() { return ""; };
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
	bool Place(std::vector<Item>* treasure) { return false; };
	//IsOpened: return false by default
	bool IsOpened() { return false; };
	//Open: return false by default
	bool Open() { return false; };
	//returns"Not Treasure" by defaults
	std::string PrintTreasure() { return "Not Treasure Square"; };
	//returns "Not Floor" by defaults
	std::string PrintUnit() { return "Not Floor"; };
	//return Wall
	std::string ToString() { return "Wall"; };
private:
	Unit* unit_ = NULL;
	std::vector<Item>* treasure_ = NULL;
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
		if (!IsOccupied()) {
			unit_ = unit;
			return true;
		}
		else {
			return false;
		}
	};
	//Place: returns false by default
	bool Place(std::vector<Item>* treasure) { return false; };
	//IsOpened: return false by default
	bool IsOpened() { return false; };
	//Open: return false by default
	bool Open() { return false; };
	//returns"Not Treasure" by defaults
	std::string PrintTreasure() { return "Not Treasure Square"; };
	//Print the unit occupying the square, Treasure square returns "empty square" if empty
	std::string PrintUnit() { 
		if (unit_ != NULL) {
			return unit_->GetName();
		}
		else {
			return "Empty Square";
		}
	};
	//return Floor
	std::string ToString() { return "Floor"; };
private:
	Unit* unit_ = NULL;
	std::vector<Item>* treasure_ = NULL;
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
	bool Place(std::vector<Item>* treasure) { treasure_ = treasure; return treasure_ == NULL; };
	//IsOpened: return true if the treasure has already been taken
	bool IsOpened() { return treasure_ == NULL; };
	//Open: return true if successfully take the treasure:
	bool Open() {
		if (!this->IsOpened()) {
			treasure_ = NULL;
			return true;
		}
		else {
			return false;
		}
	};
	//return Treasure
	std::string ToString() { return "Treasure"; };
	//Print the treasure list, Treasure square returns "empty treasure" if empty
	std::string PrintTreasure() {
		if (treasure_ != NULL) {
			std::string result;
			int n = treasure_->size();
			for (int i = 0; i < n; i++) {
				Item item = treasure_->operator[](i);
				result += item.GetName() + "\n";
			}
			return result;
		}
		else {
			return "Empty Treasure";
		}
	};
	//Print the unit occupying the square, Treasure square returns "empty square" if empty and other returns "Not Floor" by defaults
	std::string PrintUnit() { return "Not Floor"; };
private:
	std::vector<Item>* treasure_ = NULL;
	Unit* unit_ = NULL;
};