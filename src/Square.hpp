#pragma once
#include <Unit.hpp>
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
	virtual Unit Get();
	//put: takes a Unit as a parameter, place a unit into the square, return true if the def sucessfully put a unit inside
	virtual bool Put(Unit unit);
};

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
	Unit Get() { return NULL; };
	//put returns false by default
	bool Put(Unit unit) { (void)unit;  return false; };
};

class Floor : public Square {
public:
	Floor() : Square() {};
	//IsObstacle returns false by default
	const bool IsObstacle() { return false; };
	//IsOccupied
	const IsOccupied() { return unit_ != NULL };
	//clear()
	void Clear() { unit_ = NULL; };
	//get() 
	Unit Get() { return unit_; };
	//put
	bool Put(Unit unit) {
		if (!IsOccupied) {
			unit_ = unit;
			return true;
		}
		else {
			return false;
		}
	};
private:
	Unit unit_ = NULL;
};
