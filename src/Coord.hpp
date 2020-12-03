#pragma once
#ifndef COORD_HEADER
#define COORD_HEADER
#include <iostream>

class Coord : std::pair<int, int> {
public:
	Coord(int x, int y);

	int x() const;

	int y() const;

	std::string ToString();
private:
	int x_ = this->first;
	int y_ = this->second;
};

bool operator==(const Coord& a, const Coord& b);
#endif 

