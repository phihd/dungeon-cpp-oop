#pragma once
#include "World.hpp"
//#include "World.cpp"	// This is for VSCode, remove if you use visual studio
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
	Player player = Player("dm Phi");
	Game game = Game(player);
	Bot bot = game.bot;
	std::vector<Battlefield> world = game.CreateWorld();
	Battlefield room = world[2];

	for (unsigned int k = 0; k < room.ToString().size(); k++)
		std::cout << room.ToString()[k] << std::endl;
	std::cout << "----------------------------------------------------------------------------------------" << std::endl;

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