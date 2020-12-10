#include "World.hpp"
#include <algorithm>
#include <random>
#include<time.h>

Game::Game(Player player) {}

std::vector<Battlefield> Game::CreateWorld()
{
	std::vector<Battlefield> world;
	for (unsigned int i = 6; i < designs.size(); i++) {
		//Design a new room
		std::vector<std::vector<string>> lv_designs = designs[i];
		std::vector<Enemy*> lv_enemies = enemies[i];
		srand(time(0));
		auto seed = rand();
		auto rng = std::default_random_engine{};
		rng.seed(seed);
		std::shuffle(std::begin(lv_designs), std::end(lv_designs), rng);
		std::vector<string> design = lv_designs[0];
		std::vector<Item>* treasure_list = new std::vector<Item>{};
		if (i == 0 || i == 1 || i == 2) {
			seed = rand();
			rng.seed(seed);
			std::vector<Item> temp_items = items[0];
			std::shuffle(std::begin(temp_items), std::end(temp_items), rng);
			for (unsigned int j = 0; j < 5; j++)
				treasure_list->push_back(temp_items[j]);
		}
		else if (i == 3 || i == 4) {
			seed = rand();
			rng.seed(seed);
			std::vector<Item> temp_items = items[1];
			std::shuffle(std::begin(temp_items), std::end(temp_items), rng);
			for (unsigned int j = 0; j < 5; j++)
				treasure_list->push_back(temp_items[j]);
		}
		else if (i == 6 || i == 7) {
			seed = rand();
			rng.seed(seed);
			std::vector<Item> temp_items = items[2];
			std::shuffle(std::begin(temp_items), std::end(temp_items), rng);
			for (unsigned int j = 0; j < 5; j++)
				treasure_list->push_back(temp_items[j]);
		}
		else if (i == 8) {
			seed = rand();
			rng.seed(seed);
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
			new_room.EnemyArrive(lv_enemies);
		}
		else {
			std::shuffle(std::begin(lv_enemies), std::end(lv_enemies), rng);
			lv_enemies.resize(6);
			new_room.EnemyArrive(lv_enemies);
		}
		std::cout << "Room: " << i+1 << std::endl;
		for (unsigned int k = 0; k < lv_enemies.size(); k++) {
			std::cout << lv_enemies[k]->Description() << std::endl;
			std::cout << "----------------------------" << std::endl;
		}
		std::cout << "\nSpawn:" << new_room.SpawnEnemy() << std::endl;
		std::cout << std::endl;
		for (unsigned int k = 0; k < new_room.ToString().size(); k++)
			std::cout << new_room.ToString()[k] << std::endl;
		std::cout << "----------------------------------------------------------------------------------------"<< std::endl;
		world.push_back(new_room);
	}
	return world;
}