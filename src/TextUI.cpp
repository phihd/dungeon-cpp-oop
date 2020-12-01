#pragma once
#include "World.hpp"
#include <iostream>
#include "Player.hpp"
#include "Stat.hpp"
#include "Item.hpp"
using namespace std;


int main()
{
	std::cout << "###########################################################################################################" << std::endl;
	Ally* paladin = new Ally("Paladin", Stat(200, 200, 100, 75, 0), Coord(1,8));
	Ally* knight = new Ally("Knight", Stat(150, 150, 75, 75, 0), Coord(2,8));
	Ally* mage = new Ally("Mage", Stat(100, 100, 50, 25, 0), Coord(3,8));
	Ally* archer = new Ally("Archer", Stat(100, 100, 50, 0, 0), Coord(2, 7));
	Ally* heavy_archer = new Ally("Heavy Archer", Stat(100, 100, 100, 0, 0), Coord(3, 7));

	Enemy* melee = new Enemy("Melee", Stat(100, 100, 25, 50, 0), Coord(5, 7));
	Enemy* melee1 = new Enemy("Melee1", Stat(100, 100, 25, 50, 0), Coord(6, 7));
	Enemy* range = new Enemy("Range", Stat(100, 100, 40, 20, 0), Coord(6, 5));
	Enemy* range1 = new Enemy("Range1", Stat(100, 100, 40, 20, 0), Coord(6, 4));
	Enemy* canon = new Enemy("Range", Stat(200, 200, 70, 70, 0), Coord(5, 2));

	vector<Ally*> allies{ paladin, knight, mage, archer, heavy_archer };
	vector<Enemy*> enemies{ melee, melee1, range, range1, canon };

	Player player = Player("Player 1");
	player.Recruit(allies);
	Bot bot = Bot();
	bot.Recruit(enemies);
	/**************************************************************************************************************************************************************/
	std::vector<Item>* treasure_list = new std::vector<Item>{ Item("B.F Sword", "big fucking sword", Stat(0, 0, 50, 0, 0), 1300), Item("Infinity Edge", "bigger fucking sword", Stat(0, 0, 125, 0, 0), 1300) };
	
	Battlefield room(22, 14, enemies, allies, treasure_list);

	std::vector<string> design{".....###..1.###.....",
							   "...###........###...",
							   "...#.####...#...#...",
							   "##.....##...##....##",
							   "##..........########",
							   "##....##....##....##",
							   "##....##....###..###",
							   "##....##..........##",
							   "########....########",
							   "......##....##......",
							   "............##....##",
							   "......##..........##" };

	std::string temp = room.FromString(design);
	std::cout << temp << std::endl;

	std::cout << room.TreasureCoord().ToString() << std::endl;
	
	std::cout << "Ally spawn:" << std::endl;
	room.SetAllySpawn(std::vector<Coord>{Coord(1, 12), Coord(1, 11), Coord(2, 12), Coord(2, 11), Coord(3, 11)});
	std::vector<Coord> ally_spawn = room.AllySpawn();
	for (unsigned int i = 0; i < ally_spawn.size(); i++)
		std::cout << ally_spawn[i].ToString() << std::endl;
	
	bool spawn_ally = room.SpawnAlly();
	std::cout << spawn_ally << std::endl;

	std::cout << "Enemy spawn:" << std::endl;
	bool spawn_enemy = room.SpawnEnemy();
	std::cout << spawn_enemy << std::endl;
	
	std::vector<string> result = room.ToString();

	for (unsigned int i = 0; i < result.size(); i++) {
		std::cout << result[i] << std::endl;
	}
/**************************************************************************************************************************************************************/
	int turn = 0;
	int unit_turn = 0;
	bool moved = false;
	bool attacked = false;
	
	std::cout << "###########################################################################################################" << std::endl;
	std::cout << "Welcome to Dungeon Crawler Game. Type command to play the game" << std::endl;
	std::cout << "Available commands are: move, attack, use, open, quit" << std::endl;

	std::cout << "Type a command" << std::endl;
	std::string command;
	std::cin >> command;
	while (command != "quit") {
		if (turn == 0) {
			std::cout << "It's your turn" << std::endl;
			if (command == "move") {
				if (!moved) {
					std::cout << "move" << std::endl;
					moved = true;
				}
				else {
					std::cout << "Unit made its move" << std::endl;
				}
			}
			else if (command == "attack") {
				if (!attacked) {
					std::cout << "attack" << std::endl;
				}
				else {
					std::cout << "Unit already attacked";
				}
			}
			else if (command == "use")
				std::cout << "use" << std::endl;
			else if (command == "open")
				std::cout << "open" << std::endl;
			else if (command == "end turn") {
				moved = false;
				attacked = false;
				unit_turn += 1;
			}
			else {
				std::cout << "Invalid command" << std::endl;
			}
			std::cin >> command;
		}
		else {
			std::cout << "Bot's turn" << std::endl;
		}
	}
	
	return 0;
}