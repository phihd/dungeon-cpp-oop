#pragma once
#ifndef COORD_HEADER
#define COORD_HEADER
#include <iostream>

class Coord : std::pair<int, int> {
public:
	Coord(int x, int y);
	//for people how interpret coordinates as matrix
	Coord(int x, int y, bool matrix);

	int x() const;

	int y() const;

	std::string ToString();
private:
	int x_;
	int y_;
	bool matrix_ = false;
};

bool operator==(const Coord& a, const Coord& b);

bool operator!=(const Coord& a, const Coord& b);
#endif 

