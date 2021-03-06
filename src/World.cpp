#include "World.hpp"
#include <algorithm>
#include <random>
#include<time.h>

Game::Game(Player player) {}

std::vector<Battlefield> Game::CreateWorld()
{
	for (unsigned int i = 1; i < items.size(); i++) {
		std::vector<Item> current_items = items[i];
		if (i == 1) {
			for (unsigned int j = 0; j < current_items.size(); j++)
				rest1.Import(current_items[j], 5);
			rest1.Import(potions[0], 10);
			rest1.Import(potions[1], 10);
		}
		else if (i == 2) {
			for (unsigned int j = 0; j < current_items.size(); j++)
				rest2.Import(current_items[j], 5);
			rest2.Import(potions[1], 10);
			rest2.Import(potions[2], 10);
		}
		else {
			for (unsigned int j = 0; j < current_items.size(); j++)
				rest3.Import(current_items[j], 5);
			rest3.Import(potions[2], 10);
			rest3.Import(potions[3], 10);
		}
	}
	rests = {rest1, rest2, rest3};
	for (unsigned int i = 0; i < allies.size(); i++) {
		allies[i]->FullHeal();
	}
	for (unsigned int i = 0; i < enemies.size(); i++) {
		for (unsigned int j = 0; j < enemies[i].size(); j++)
			enemies[i][j]->FullHeal();
	}
	std::vector<Battlefield> world;
	for (unsigned int i = 0; i < designs.size(); i++) {
		//Design a new room
		std::vector<std::vector<string>> lv_designs = designs[i];
		std::vector<Unit*> lv_enemies = enemies[i];
		srand(time(0));
		auto seed = rand();
		auto rng = std::default_random_engine{};
		rng.seed(seed);
		std::shuffle(std::begin(lv_designs), std::end(lv_designs), rng);
		std::vector<string> design = lv_designs[0];
		std::vector<Item>* treasure_list = new std::vector<Item>{};
		if (i == 0 || i == 1 || i == 2) {
			seed = rand();
			rng.seed(seed + i);
			std::vector<Item> temp_items = items[0];
			std::shuffle(std::begin(temp_items), std::end(temp_items), rng);
			for (unsigned int j = 0; j < 5; j++)
				treasure_list->push_back(temp_items[j]);
		}
		else if (i == 3 || i == 4) {
			seed = rand();
			rng.seed(seed + i);
			std::vector<Item> temp_items = items[1];
			std::shuffle(std::begin(temp_items), std::end(temp_items), rng);
			for (unsigned int j = 0; j < 5; j++)
				treasure_list->push_back(temp_items[j]);
		}
		else if (i == 6 || i == 7) {
			seed = rand();
			rng.seed(seed + i);
			std::vector<Item> temp_items = items[2];
			std::shuffle(std::begin(temp_items), std::end(temp_items), rng);
			for (unsigned int j = 0; j < 5; j++)
				treasure_list->push_back(temp_items[j]);
		}
		else if (i == 8) {
			seed = rand();
			rng.seed(seed + i);
			std::vector<Item> temp_items = items[3];
			std::shuffle(std::begin(temp_items), std::end(temp_items), rng);
			for (unsigned int j = 0; j < 5; j++)
				treasure_list->push_back(temp_items[j]);
		}
		Battlefield new_room = Battlefield(22, 14, {}, {}, treasure_list);
		new_room.FromString(design);
		//Set spawn for allies
		std::vector<Coord> spawn = spawns[i];
		new_room.SetAllySpawn(spawn);
		//Set spawn for enemies and randomize enemies
		srand(time(0));
		seed = rand();
		rng.seed(seed);
		if ((i == 3 || i == 6 || i == 9)) {
			if (i == 3)
				new_room.SetEnemySpawn(boss_spawns[0]);
			else if (i == 6)
				new_room.SetEnemySpawn(boss_spawns[1]);
			else if (i == 9)
				new_room.SetEnemySpawn(boss_spawns[2]);
			new_room.UnitArrive(lv_enemies);
		}
		else {
			std::shuffle(std::begin(lv_enemies), std::end(lv_enemies), rng);
			lv_enemies.resize(6);
			new_room.UnitArrive(lv_enemies);
		}
		new_room.SpawnEnemy();
		/**
		std::cout << "Room: " << i+1 << std::endl;
		for (unsigned int k = 0; k < lv_enemies.size(); k++) {
			std::cout << lv_enemies[k]->Description() << std::endl;
			std::cout << "----------------------------" << std::endl;
		}
		std::cout << std::endl;
		for (unsigned int k = 0; k < new_room.ToString().size(); k++)
			std::cout << new_room.ToString()[k] << std::endl;
		std::cout << "----------------------------------------------------------------------------------------"<< std::endl;
		*/
		world.push_back(new_room);
	}
	return world;
}