#pragma once
#include "World.hpp"
#include <iostream>
#include "Player.hpp"
#include "Stat.hpp"
#include "Item.hpp"
using namespace std;


int main() 
{
	std::vector<Item>* treasure_list = new std::vector<Item>{ Item("B.F Sword", "big fucking sword", Stat(0, 0, 50, 0, 0), 1300), Item("Infinity Edge", "bigger fucking sword", Stat(0, 0, 125, 0, 0), 1300) };

	Battlefield room(10, 10, {}, {}, treasure_list, {});

	//room.AddTreasure(Coord(5, 5));
	//Square* treasure = room.Apply(Coord(5, 5));
	//bool temp = treasure->Place(treasure_list);
	//std::cout << treasure->ToString() << std::endl;
	//std::cout << temp << std::endl;
	//std::cout << treasure->PrintTreasure() << std::endl;
	std::vector<std::string> result = room.ToString();
	for (unsigned int i = 0; i < result.size(); i++) {
		std::cout << result[i] << std::endl;
	}

	std::vector<string> design{"........",
							   "........",
							   "###..###",
							   "#...1..#",
							   "#......#",
							   "###..###",
							   "........",
							   "........"}; 
	
	std::string temp = room.FromString(design);
	std::cout << temp << std::endl;
	result = room.ToString();

	for (unsigned int i = 0; i < result.size(); i++) {
		std::cout << result[i] << std::endl;
	}
	
	return 0;
}