#pragma once
#ifndef COORD_HEADER
#define COORD_HEADER
#include <iostream>

class Coord : std::pair<int, int> {
public:
	Coord(int x, int y);

	int x();

	int y();

	std::string ToString();
private:
	int x_ = this->first;
	int y_ = this->second;
};
#endif 

