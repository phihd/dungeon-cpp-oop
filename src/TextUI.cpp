#pragma once
#include "World.hpp"
#include <iostream>
#include "Player.hpp"
#include "Stat.hpp"
#include "Item.hpp"
using namespace std;


int main()
{
	Ally* paladin = new Ally("Paladin", Stat(200, 200, 100, 75, 0));
	Ally* knight = new Ally("Knight", Stat(150, 150, 75, 75, 0));
	Ally* mage = new Ally("Mage", Stat(100, 100, 50, 25, 0));
	Ally* archer = new Ally("Archer", Stat(100, 100, 50, 0, 0));
	Ally* heavy_archer = new Ally("Heavy Archer", Stat(100, 100, 100, 0, 0));

	Enemy* melee = new Enemy("Melee", Stat(100, 100, 25, 50, 0));
	Enemy* melee1 = new Enemy("Melee1", Stat(100, 100, 25, 50, 0));
	Enemy* range = new Enemy("Range", Stat(100, 100, 40, 20, 0));
	Enemy* range1 = new Enemy("Range1", Stat(100, 100, 40, 20, 0));
	Enemy* canon = new Enemy("Range", Stat(200, 200, 70, 70, 0));

	vector<Ally*> allies{ paladin, knight, mage, archer, heavy_archer };
	vector<Enemy*> enemies{ melee, melee1, range, range1, canon };

	std::vector<Item>* treasure_list = new std::vector<Item>{ Item("B.F Sword", "big fucking sword", Stat(0, 0, 50, 0, 0), 1300), Item("Infinity Edge", "bigger fucking sword", Stat(0, 0, 125, 0, 0), 1300) };

	Battlefield room(10, 10, {}, {}, treasure_list, {});
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