#pragma once
#ifndef GAME_HEADER
#define GAME_HEADER

//#include "Room.hpp"
//#include "Room.cpp"		// This is for VSCode, remove if you use visual studio
#include "Player.hpp"
//#include "Player.cpp"
#include <map>

class Game {
public:
	Game(Player player);
	//World map
	/*Sketch of world: Rest0 -> Stage1 -> Stage2 -> Rest1 -> Stage3 -> Boss1 -> Rest2 -> Stage5 -> Stage6 -> Boss2 
					-> Rest3 -> Stage8 -> Stage9 -> Final Boss;
	*/
	//Designs of Stage1
	std::vector<string> room1lv1{"#......#",
								 ".#....#.",
								 "..#..#..",
								 "..#..#..",
								 "#......#",
								 "........",
								 "........",
								 "........" };
	std::vector<string> room1lv2{"........",
								 "........",
								 "###..###",
								 "#......#",
								 "#......#",
								 "###..###",
								 "........",
								 "........" };
	//Designs of Stage2
	//Designs of Stage3
	//Designs of Boss1
	//Designs of Stage5
	//Designs of Stage6
	//Designs of Boss2
	//Designs of Stage8
	//Designs of Stage9
	//Designs of FinalBoss


	//Player
	Bot bot = Bot("Bot 1");



	//Unit
	//Units of Stage1
	//Units of Stage2
	//Units of Stage3
	//Units of Boss1
	//Units of Stage5
	//Units of Stage6
	//Units of Boss2
	//Units of Stage8
	//Units of Stage9
	//Units of FinalBoss
	//Item
	//Make game

private:
};
#endif
