#pragma once
#include "World.hpp"
#include "World.cpp"	// This is for VSCode, remove if you use visual studio
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
	Unit* paladin = new Unit("Paladin", Stat(400, 400, 100, 75, 0, 6, 1));
  	Unit* knight = new Unit("Knight", Stat(300, 300, 75, 75, 0, 5, 1));
  	Unit* mage = new Unit("Mage", Stat(200, 200, 50, 25, 50, 4, 5));
  	Unit* archer = new Unit("Archer", Stat(200, 200, 50, 50, 0, 4, 4));
  	Unit* sniper = new Unit("Heavy Archer", Stat(200, 200, 100, 50, 0, 3, 5));
  	Unit* valkyrie = new Unit("Valkyrie", Stat(300, 300, 100, 80, 0, 5, 1));
  	Unit* assassin = new Unit("Assassin", Stat(300, 300, 175, 90, 0, 7, 1));
  	Unit* wizard = new Unit("Grand Wizard", Stat(200, 200, 120, 50, 0, 3, 5));
  	Unit* guardian = new Unit("Guardian", Stat(500, 500, 50, 200, 0, 4, 1));
  	Unit* swordman = new Unit("Sword man", Stat(300, 300, 100, 60, 0, 6, 1));

	Unit* melee = new Unit("Melee", Stat(100, 100, 25, 50, 0, 1, 3), false);
	Unit* melee1 = new Unit("Melee1", Stat(100, 100, 25, 50, 0, 1, 4), false);
	Unit* range = new Unit("Range", Stat(100, 100, 40, 20, 0, 4, 2), false);
	Unit* range1 = new Unit("Range1", Stat(100, 100, 40, 20, 0, 4, 3), false);
	Unit* canon = new Unit("Canon", Stat(200, 200, 70, 70, 0, 5, 1), false);

	vector<Unit*> allies_u{ paladin, knight, mage, archer, sniper };
	vector<Unit*> allies{ paladin, knight, mage, archer, sniper };
	vector<Unit*> enemies_u{ melee, melee1, range, range1, canon };
	vector<Unit*> enemies{ melee, melee1, range, range1, canon };

	Player player = Player("Player 1");
	player.Recruit(paladin);
	Bot bot = Bot("Bot 1");
	bot.Recruit(enemies_u);
	/**************************************************************************************************************************************************************/
	//Game game(player);
	 
	std::vector<Item>* treasure_list = new std::vector<Item>{ Item("B.FSword", "big fucking sword", Stat(0, 0, 50, 0, 0, 0, 0), 1300), 
		Item("InfinityEdge", "bigger fucking sword", Stat(0, 0, 125, 0, 0, 0, 0), 1300) };
	
	Battlefield room(22, 14, enemies, allies, treasure_list);

	player.Enter(&room);

	player.AddItem(Item("B.FSword", "big fucking sword", Stat(0, 0, 50, 0, 0, 0, 0), 1300), 1);
	player.AddItem(Item("InfinityEdge", "bigger fucking sword", Stat(0, 0, 125, 0, 0, 0, 0), 3200), 1);

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
	cout << "equip Malphite InfinityEdge" << endl;
	cout << "consume Garen CorruptingPotion" << endl;
	cout << Item("B.FSword", "big fucking sword", Stat(0, 0, 50, 0, 0, 0, 0), 1300).FullDescription() << endl;
	player.Equip(Item("B.FSword", "big fucking sword", Stat(0, 0, 50, 0, 0, 0, 0), 1300), paladin);
	cout << paladin->Description() << endl;

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
					cout << "Unit is not in the army." << endl;
				else {
					cout << player.Move(unit, Coord(stoi(cmd_split[2]), stoi(cmd_split[3]))) << endl;
				}
			}
			else if (cmd_split[1] == "attack") {
				Unit* ally = player.GetUnit(cmd_split[0]);
				if (!ally) 
					cout << "Unit is not in the army." << endl;
				Unit* enemy = bot.GetUnit(cmd_split[2]);
				if (!enemy) 
					cout << "Enemy doesn't exist." << endl;
				else
					cout << player.Attack(ally, enemy) << endl;
				
			}
			else if (cmd_split[0] == "location") {
				Unit* unit = player.GetUnit(cmd_split[1]);
				if (!unit) 
					cout << "Unit is not in the army." << endl;
				else
					cout << "Location: " << unit->GetLocation().ToString() << endl;
			}
			else if (cmd_split[0] == "equip") {
				Unit* unit = player.GetUnit(cmd_split[1]);
				if (!unit) 
					cout << "Unit is not in the army." << endl;
				cout << "*Before equip:\n";
				cout << unit->Description() << endl;
				player.Equip(Item("B.FSword", "big fucking sword", Stat(0, 0, 50, 0, 0, 0, 0), 1300), unit);
				cout << "*After equip:\n";
				cout << unit->Description() << endl;
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