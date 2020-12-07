#pragma once
#include "World.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <random>
#include<time.h>

using namespace std;

template <class Container>
void split1(const std::string& str, Container& cont)
{
    std::istringstream iss(str);
    std::copy(std::istream_iterator<std::string>(iss),
         std::istream_iterator<std::string>(),
         std::back_inserter(cont));
}


int main()
{
	std::cout << "###########################################################################################################" << std::endl;
	Ally* paladin = new Ally("Paladin", Stat(200, 200, 100, 75, 0), 1);
	Ally* knight = new Ally("Knight", Stat(150, 150, 75, 75, 0), 2);
	Ally* mage = new Ally("Mage", Stat(100, 100, 50, 25, 0), 3);
	Ally* archer = new Ally("Archer", Stat(100, 100, 50, 0, 0), 4);
	Ally* heavy_archer = new Ally("Heavy Archer", Stat(100, 100, 100, 0, 0), 5);

	Enemy* melee = new Enemy("Melee", Stat(100, 100, 25, 50, 0), 1);
	Enemy* melee1 = new Enemy("Melee1", Stat(100, 100, 25, 50, 0), 1);
	Enemy* range = new Enemy("Range", Stat(100, 100, 40, 20, 0), 4);
	Enemy* range1 = new Enemy("Range1", Stat(100, 100, 40, 20, 0), 4);
	Enemy* canon = new Enemy("Canon", Stat(200, 200, 70, 70, 0), 5);

	vector<Unit*> allies_u{ paladin, knight, mage, archer, heavy_archer };
	vector<Ally*> allies{ paladin, knight, mage, archer, heavy_archer };
	vector<Unit*> enemies_u{ melee, melee1, range, range1, canon };
	vector<Enemy*> enemies{ melee, melee1, range, range1, canon };

	Player player = Player("Player 1");
	player.Recruit(allies_u);
	Bot bot = Bot("Bot 1");
	bot.Recruit(enemies_u);
	/**************************************************************************************************************************************************************/
	std::vector<Item>* treasure_list = new std::vector<Item>{ Item("B.F Sword", "big fucking sword", Stat(0, 0, 50, 0, 0), 1300), Item("Infinity Edge", "bigger fucking sword", Stat(0, 0, 125, 0, 0), 1300) };
	
	Battlefield room(22, 14, enemies, allies, treasure_list);

	player.Enter(&room);
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

	room.SetAllySpawn(std::vector<Coord>{Coord(1, 12), Coord(1, 11), Coord(2, 12), Coord(2, 11), Coord(3, 11)});
	
	room.SpawnAlly();

	room.SpawnEnemy();

	/**
	std::vector<Coord> available_coord = room.BFS(Coord(3, 11), 5);
	for (unsigned int i = 0; i < available_coord.size(); i++)
		std::cout << available_coord[i].ToString() << std::endl;
	srand(time(0));
	auto seed = rand();
	auto rng = std::default_random_engine{};
	rng.seed(seed);
	std::shuffle(std::begin(available_coord), std::end(available_coord), rng);
	*/
	
	vector<string> result = room.ToString();
	for (unsigned int i = 0; i < result.size(); i++) {
		std::cout << result[i] << std::endl;
	}
	std::cout << std::endl;

	vector<vector<int>>int_result = room.ToInt();
	for (unsigned int i = 0; i < int_result.size(); i++) {
		//std::cout << i << std::endl;
		for (unsigned int j = 0; j < int_result[i].size(); j++)
			std::cout << int_result[i][j];
		std::cout << std::endl;
	}
	std::cout << int_result.size() << "x" << int_result[1].size() << std::endl;
	/**
	std::vector<Coord> avai_coords = room.BFS(Coord(6, 11), 4);
	for (unsigned int i = 0; i < avai_coords.size(); i++)
		std::cout << avai_coords[i].ToString() << std::endl;
		*/
/**************************************************************************************************************************************************************/
	int turn = 0;
	int unit_turn = 0;
	bool moved = false;
	bool attacked = false;
	
	std::cout << "###########################################################################################################" << std::endl;
	std::cout << "Welcome to Dungeon Crawler Game. Type command to play the game" << std::endl;
	std::cout << "Available commands are: move, attack, use, open, quit" << std::endl;
	cout << "For example:" << endl;
	cout << "move Kai'sa 2 3" << endl;
	cout << "Kai'sa attack Cho'Gath" << endl;
/**
	std::string command;
	do {
		player.startNewTurn();
		// Player's turn
		do {
			std::cout << "It's your turn, type a command:" << std::endl;
			getline(cin, command);
			vector<string> cmd_split;
			split1(command, cmd_split);

			if (cmd_split[0] == "move") {
				Unit* unit = player.GetUnit(cmd_split[1]);
				if (!unit) 
					cout << "Unit is not in the army" << endl;
				else
					cout << player.Move(unit, Coord(stoi(cmd_split[2]), stoi(cmd_split[3]))) << endl;
			}
			else if (cmd_split[1] == "attack") {
				Unit* ally = player.GetUnit(cmd_split[0]);
				if (!ally) 
					cout << "Unit is not in the army" << endl;
				Unit* enemy = bot.GetUnit(cmd_split[2]);
				if (!enemy) 
					cout << "Enemy doesn't exist." << endl;
				else
					cout << player.Attack(ally, enemy) << endl;
				
			}
			else if (command == "end turn" || command == "quit")
				break;
			else
				std::cout << "Invalid command" << std::endl;
		} while (true);

	/**
		// Bot's turn
		std::cout << "Bot's turn" << std::endl;
		// Each enemy take a move and an attack
		for (int i = 0; i < bot.GetArmy().size(); i++) {
			Unit* enemy = bot.GetArmy()[i];
			auto possible_new_locations = room.BFS(enemy->GetLocation(), enemy->GetRange());
			auto new_location = possible_new_locations[rand() % possible_new_locations.size()];
			bot.Move(enemy, new_location);
			enemy->Attack(player.GetArmy()[rand() % player.GetArmy().size()]);
		}
		*/
	//} while (command != "quit");
	return 0;
}