#pragma once
#include "World.hpp"
#include <iostream>

#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <random>

using namespace std;

template <class Container>
void split1(const std::string& str, Container& cont)
{
    std::istringstream iss(str);
    std::copy(std::istream_iterator<std::string>(iss),
         std::istream_iterator<std::string>(),
         std::back_inserter(cont));
}

void PrintRoomInt(Battlefield room) {
	// Background		|	0
	// Ally				|	1 -> 5
	// Enemy			|	-1 -> -n
	// Wall				| 	6
	// Opened Treasure	|	7
	// Closed Treasure 	|	8
	auto int_result = room.ToInt();
	for (unsigned int i = 0; i < int_result.size(); i++) {
		//std::cout << i << std::endl;
		for (unsigned int j = 0; j < int_result[i].size(); j++)
			std::cout << int_result[i][j];
		std::cout << std::endl;
	}
	std::cout << int_result.size() << "x" << int_result[1].size() << std::endl;
}


int main()
{
	// Create units
	std::cout << "###########################################################################################################" << std::endl;
	Ally* paladin = new Ally("Paladin", Stat(200, 200, 100, 75, 0, 1, 5));
	Ally* knight = new Ally("Knight", Stat(150, 150, 75, 75, 0, 2, 3));
	Ally* mage = new Ally("Mage", Stat(100, 100, 50, 25, 0, 3, 4));
	Ally* archer = new Ally("Archer", Stat(100, 100, 50, 0, 0, 4, 1));
	Ally* heavy_archer = new Ally("HeavyArcher", Stat(100, 100, 100, 0, 0, 5, 20));

	Enemy* melee = new Enemy("Melee", Stat(100, 100, 25, 50, 0, 1, 3));
	Enemy* melee1 = new Enemy("Melee1", Stat(100, 100, 25, 50, 0, 1, 4));
	Enemy* range = new Enemy("Range", Stat(100, 100, 40, 20, 0, 4, 2));
	Enemy* range1 = new Enemy("Range1", Stat(100, 100, 40, 20, 0, 4, 3));
	Enemy* canon = new Enemy("Canon", Stat(200, 200, 70, 70, 0, 5, 1));

	vector<Unit*> allies_u{ paladin, knight, mage, archer, heavy_archer };
	vector<Ally*> allies{ paladin, knight, mage, archer, heavy_archer };
	vector<Unit*> enemies_u{ melee, melee1, range, range1, canon };
	vector<Enemy*> enemies{ melee, melee1, range, range1, canon };

	Player player = Player("Player 1");
	player.Recruit(allies_u);
	Bot bot = Bot("Bot 1");
	bot.Recruit(enemies_u);
	/**************************************************************************************************************************************************************/
	std::vector<Item>* treasure_list = new std::vector<Item>{ Item("B.F Sword", "big fucking sword", Stat(0, 0, 50, 0, 0, 0, 0), 1300), 
		Item("Infinity Edge", "bigger fucking sword", Stat(0, 0, 125, 0, 0, 0, 0), 1300) };
	
	Battlefield room(22, 14, enemies, allies, treasure_list);

	player.Enter(&room);

	bot.Enter(&room);

	std::vector<string> result = room.ToString();
	for (unsigned int i = 0; i < result.size(); i++) {
		std::cout << result[i] << std::endl;
	}
	std::cout << std::endl;

	PrintRoomInt(room);

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
	
	result = room.ToString();
	for (unsigned int i = 0; i < result.size(); i++) {
		std::cout << result[i] << std::endl;
	}
	std::cout << std::endl;

	PrintRoomInt(room);
	/**
	std::vector<Coord> avai_coords = room.BFS(Coord(6, 11), 4);
	for (unsigned int i = 0; i < avai_coords.size(); i++)
		std::cout << avai_coords[i].ToString() << std::endl;
		*/
/**************************************************************************************************************************************************************/
	// A turn-based match between player vs Bot
	int turn = 0;
	int unit_turn = 0;
	bool moved = false;
	bool attacked = false;
	
	std::cout << "###########################################################################################################" << std::endl;
	std::cout << "Welcome to Dungeon Crawler Game. Type command to play the game" << std::endl;
	std::cout << "Available commands are: move, attack, location, equip, consume" << std::endl;
	cout << "For example:" << endl;
	cout << "move Kai'sa 2 3" << endl;
	cout << "Kai'sa attack Cho'Gath" << endl;
	cout << "location Talon" << endl;
	cout << "equip InfinityEdge" << endl;
	cout << "consume CorruptingPotion" << endl;

	// Background		|	0
	// Ally				|	1 -> 5		|	Paladin, Knight, Mage, Archer, Heavy Archer
	// Enemy			|	-1 -> -5	|	Melee, Melee1, Range, Range1, Canon
	// Wall				| 	6
	// Opened Treasure	|	7
	// Closed Treasure 	|	8
	std::string command;
	do {
		player.startNewTurn();
		// Player's turn
		do {
			std::cout << "\nIt's your turn, type a command:" << std::endl;
			getline(cin, command);
			vector<string> cmd_split;
			split1(command, cmd_split);

			if (cmd_split[0] == "move") {
				Unit* unit = player.GetUnit(cmd_split[1]);
				if (!unit) 
					cout << "Unit is not in the army" << endl;
				else {
					cout << player.Move(unit, Coord(stoi(cmd_split[2]), stoi(cmd_split[3]))) << endl;
				}
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
			else if (cmd_split[0] == "location") {
				Unit* unit = player.GetUnit(cmd_split[1]);
				if (!unit) 
					cout << "Unit is not in the army" << endl;
				else
					cout << "Location: " << unit->GetLocation().ToString() << endl;
			}
			else if (command == "end turn" || command == "quit")
				break;
			else
				std::cout << "Invalid command" << std::endl;
			PrintRoomInt(room);
			
		} while (true);

		// Bot's turn
		bot.startNewTurn();
		std::cout << "Bot's turn" << std::endl;
		// Each enemy take a move and an attack
		for (int i = 0; i < bot.GetArmy().size(); i++) {
			Unit* enemy = bot.GetArmy()[i];
			cout << enemy->Description() << endl;
			auto possible_new_locations = room.BFS(enemy->GetLocation(), enemy->GetMoveRange());

			if (!possible_new_locations.empty()) {
				auto new_location = possible_new_locations[rand() % possible_new_locations.size()];
				cout << bot.Move(enemy, new_location) << endl;
			}

			auto possible_ally_locations = room.BFS_Attack(enemy->GetLocation(), enemy->GetAttackRange());
			if (!possible_ally_locations.empty()) {
				auto new_ally = room.Apply(possible_ally_locations[rand() % possible_ally_locations.size()])->Get();
				cout << bot.Attack(enemy, new_ally) << endl;
			}
		}
	} while (command != "quit");
	return 0;
}