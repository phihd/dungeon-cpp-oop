#pragma once
#ifndef WORLD_HEADER
#define WORLD_HEADER

#include "Room.hpp"
#include <map>

class World {
public:
	World(std::map<Room, std::vector<Room>> world_tree);
	//World map
	/*Sketch of world: Rest0 -> Stage1 -> Stage2 -> Rest1 -> Stage3 -> Boss1 -> Rest2 -> Stage5 -> Stage6 -> Boss2 
					-> Rest3 -> Stage8 -> Stage9 -> Final Boss;
	*/

	std::vector<string> room1lv1{"#......#",
								 ".#....#.",
								 "..#..#..",
								 "..#..#..",
								 "#......#",
								 "........",
								 "........",
								 "........" } ;
	std::vector<string> room1lv2{"........",
								 "........",
								 "###..###",
								 "#......#",
								 "#......#",
								 "###..###",
								 "........",
								 "........" };
	//Player
	//Unit
	//Item

private:
};
#endif
