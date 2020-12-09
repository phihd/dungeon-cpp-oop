#include "World.hpp"
#include <algorithm>
#include <random>
#include<time.h>

Game::Game(Player player) {}

std::vector<Room> Game::CreateWorld()
{
	std::vector<Room> world;
	for (unsigned int i = 0; i < designs.size(); i++) {
		//Design a new room
		std::vector<std::vector<string>> lv_designs = designs[i];
		std::vector<Enemy*> lv_enemies = enemies[i];
		std::vector<std::vector<Item>> temp_items = items;
		srand(time(0));
		auto seed = rand();
		auto rng = std::default_random_engine{};
		rng.seed(seed);
		std::shuffle(std::begin(lv_designs), std::end(lv_designs), rng);
		std::vector<string> design = lv_designs[i];
		std::vector<Item> treasure_list = {};
		if (i == 0 || i == 1) {
			auto seed = rand();
			auto rng = std::default_random_engine{};
			rng.seed(seed);
			std::shuffle(std::begin(temp_items[0]), std::end(temp_items[0]), rng);
			temp_items[0].resize(5);
			std::vector<Item> treasure_list = temp_items[0];
		}
		else if (i == 3 || i == 4) {
			auto seed = rand();
			auto rng = std::default_random_engine{};
			rng.seed(seed);
			std::shuffle(std::begin(temp_items[1]), std::end(temp_items[1]), rng);
			temp_items[0].resize(5);
			std::vector<Item> treasure_list = temp_items[1];
		}
		else if (i == 5 || i == 7) {
			auto seed = rand();
			auto rng = std::default_random_engine{};
			rng.seed(seed);
			std::shuffle(std::begin(temp_items[2]), std::end(temp_items[2]), rng);
			temp_items[0].resize(5);
			std::vector<Item> treasure_list = temp_items[2];
		}
		else if (i == 8) {
			auto seed = rand();
			auto rng = std::default_random_engine{};
			rng.seed(seed);
			std::shuffle(std::begin(temp_items[3]), std::end(temp_items[3]), rng);
			temp_items[0].resize(5);
			std::vector<Item> treasure_list = temp_items[3];
		}
		Battlefield new_room = Battlefield(22, 14, {}, {}, &treasure_list);
		new_room.FromString(design);
		//Set spawn for allies
		std::vector<Coord> spawn = spawns[i];
		new_room.SetAllySpawn(spawn);
		//Set spawn for enemies and randomize enemies
		srand(time(0));
		auto seed = rand();
		auto rng = std::default_random_engine{};
		rng.seed(seed);
		if ((i == 2 || i == 7 || i == 9)) {
			new_room.SetEnemySpawn(boss_spawns[i]);
			new_room.EnemyArrive(lv_enemies);
		}
		else {
			std::shuffle(std::begin(lv_enemies), std::end(lv_enemies), rng);
			lv_enemies.resize(6);
			new_room.EnemyArrive(lv_enemies);
		}
		world.push_back(new_room);
	}
	return world;
}
