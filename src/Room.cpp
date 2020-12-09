#include "Room.hpp"
#include <algorithm>
#include <random>
#include<time.h>

Room::Room() {}

string Room::type()
{
	return "Room";
}

Rest::Rest(std::vector<Item>* stock) : Room(), stock_(stock) {}

std::vector<Item>* Rest::Stock()
{
	return stock_;
}

string Rest::type()
{
	return "Rest";
}

void Rest::Import(std::vector<Item> items)
{
	for (unsigned int i = 0; i < items.size(); i++) {
		Item item = items[i];
		stock_->push_back(item);
	}
}

Battlefield::Battlefield(int nrows, int ncols, std::vector<Enemy*> enemies, std::vector<Ally*> allies,
	std::vector<Item>* treasures) : Grid(nrows, ncols), Room(), enemies_(enemies), allies_(allies), treasures_(treasures)
{
	for (int x = 0; x < this->Rows(); x++) {
		for (int y = 0; y < this->Cols(); y++) {
			if (x > 0 && x < nrows - 1 && y > 0 && y < ncols - 1)
				this->Update(Coord(x, y), new Floor);
			else
				this->Update(Coord(x, y), new Wall);
		}
	}
}

void Battlefield::AddWall(Coord coord) {
	this->Update(coord, new Wall);
}

void Battlefield::AddTreasure(Coord coord) {
	this->Update(coord, new Treasure);
}

std::string Battlefield::PutTreasure(Coord coord) {
	Square* current = this->Apply(coord);
	if (current->ToString() != "Treasure") {
		return "Not Treasure Square";
	}
	else {
		bool result = current->Place(treasures_);
		if (!result)
			return "Place Treasure Fail";
		else
			return "Successs";
	}
}

bool Battlefield::AddUnit(Coord coord, Unit* unit) {
	Square* current = this->Apply(coord);
	bool result = current->Put(unit);
	return result;
}

bool Battlefield::RemoveUnit(Coord coord, Unit* unit)
{
	if (unit->GetLocation() != coord)
		return false;
	this->Apply(coord)->Clear();
	return true;
}
/**
bool Battlefield::Movable(Coord coord, Unit* unit) {
	Coord origin = unit->GetLocation();
	std::vector<Coord> available_coords = this->BFS(coord, unit->GetRange());
	Square* current = this->Apply(coord);
	if (current->IsObstacle() || current->IsOccupied())
		return false;
	if (std::find(std::begin(available_coords), std::end(available_coords), coord) == std::end(available_coords))
		return false;
	return true;
}
*/
bool Battlefield::MoveUnit(Coord coord, Unit* unit)
{
	Coord origin = unit->GetLocation();
	if (this->RemoveUnit(origin, unit) && this->AddUnit(coord, unit) && !unit->HasMoved())
		return true;
	else
	{
		if ((!this->AddUnit(coord, unit) && origin != Coord(-1, -1)) || unit->HasMoved()) {
			this->AddUnit(origin, unit);
		}
		return false;
	}
}

std::string Battlefield::FromString(std::vector<string> room) {
	for (unsigned int y = 0; y < room.size(); y++) {
		std::string row = room[y];
		for (unsigned int x = 0; x < row.length(); x++) {
			Coord coord = Coord(x + 1, y + 1);
			char c = row[x];
			if (c == '#') {
				this->AddWall(coord);
			}
			else if (c == '.') {
				continue;
			}
			else if (c == '0' || c == '1') {
				this->AddTreasure(coord);
				if (c == '1') {
					std::string result = this->PutTreasure(coord);
					if (result == "Place Treasure Fail") {
						return result;
					}
				}
			}
			else {
				return "Wrong format";
			}
		}
	}
	return "Success";
}

std::vector<string> Battlefield::ToString() {
	std::vector<string> result;
	for (int y = 0; y < this->Cols(); y++) {
		string row;
		for (int x = 0; x < this->Rows(); x++) {
			Coord coord = Coord(x, y);
			Square* square = this->Apply(coord);
			if (square->ToString() == "Wall")
				row += "#";
			else if (square->ToString() == "Floor") {
				if (square->IsOccupied()) {
					Unit* occupant = square->Get();
					if (occupant->ToString() == "Ally") {
						string ally;
						for (unsigned int i = 0; i < allies_.size(); i++) {
							if (occupant->GetName() == allies_[i]->GetName()) {
								ally = std::to_string(i);
								break;
							}
						}
						row += ally;
					}
					else if (occupant->ToString() == "Enemy") {
						string enemy;
						for (unsigned int i = 0; i < enemies_.size(); i++) {
							if (occupant->GetName() == enemies_[i]->GetName()) {
								enemy = std::to_string(i);
								break;
							}
						}
						row += enemy;
					}
					else
						row += "u";
				}
				else
					row += ".";
			}
			else if (square->ToString() == "Treasure") {
				if (square->IsOpened())
					row += "o";
				else
					row += "c";
			}
			else
				continue;
		}
		result.push_back(row);
	}
	return result;
}

std::vector<std::vector<int>> Battlefield::ToInt() {
	std::vector<std::vector<int>> result;
	for (int y = 0; y < this->Cols(); y++) {
		//result.resize(12, std::vector<int>());
		std::vector<int> row;
		for (int x = 0; x < this->Rows(); x++) {
			Coord coord = Coord(x, y);
			Square* square = this->Apply(coord);
			if (square->ToString() == "Wall")
				row.push_back(6);
			else if (square->ToString() == "Floor") {
				if (square->IsOccupied()) {
					Unit* occupant = square->Get();
					if (occupant->ToString() == "Ally") {
						int ally;
						for (unsigned int i = 0; i < allies_.size(); i++) {
							if (occupant->GetName() == allies_[i]->GetName()) {
								ally = i + 1;
								break;
							}
						}
						row.push_back(ally);
					}
					else if (occupant->ToString() == "Enemy") {
						int enemy;
						for (unsigned int i = 0; i < enemies_.size(); i++) {
							if (occupant->GetName() == enemies_[i]->GetName()) {
								enemy = i + 1;
								enemy = -enemy;
								break;
							}
						}
						row.push_back(enemy);
					}
					else
						row.push_back(9);
				}
				else
					row.push_back(0);
			}
			else if (square->ToString() == "Treasure") {
				if (square->IsOpened())
					row.push_back(7);
				else
					row.push_back(8);
			}
			else
				continue;
		}
		result.push_back(row);
	}
	return result;
}

void Battlefield::SetAllySpawn(std::vector<Coord> spawns) {
	ally_spawn_ = spawns;
}

void Battlefield::SetEnemySpawn(std::vector<Coord> spawns) {
	enemy_spawn_ = spawns;
}

std::vector<Coord> Battlefield::AllySpawn()
{
	return ally_spawn_;
}

std::vector<Coord> Battlefield::EnemySpawn()
{
	return enemy_spawn_;
}

bool Battlefield::SpawnAlly() {
	if (ally_spawn_.empty())
		return false;
	for (unsigned int i = 0; i < std::min(allies_.size(), ally_spawn_.size()); i++) {
		Ally* ally = allies_[i];
		Coord spawn = ally_spawn_[i];
		if (ally->IsAlive()) {
			bool temp = this->AddUnit(spawn, ally);
			if (!temp)
				return false;
			ally->Move(spawn);
		}
	}
	return true;
}

bool Battlefield::SpawnEnemy() {
	srand(time(0));
	auto seed = rand();
	if (enemy_spawn_.empty()) {
		std::vector<Coord> available_coord = {};
		//find all empty square
		for (int x = 0; x < this->Rows(); x++) {
			for (int y = 0; y < this->Cols(); y++) {
				Coord coord = Coord(x, y);
				Square* square = this->Apply(coord);
				bool available = true;
				for (unsigned int i = 0; i < ally_spawn_.size(); i++) {
					Coord spawn = ally_spawn_[i];
					if (spawn == coord) {
						available = false;
						break;
					}
				}
				if (square->ToString() == "Floor" && available && !square->IsOccupied())
					available_coord.push_back(coord);
			}
		}
		//shuffle the empty square coordinates
		auto rng = std::default_random_engine{};
		rng.seed(seed);
		std::shuffle(std::begin(available_coord), std::end(available_coord), rng);
		//put unit
		for (unsigned int i = 0; i < enemies_.size(); i++) {
			Coord coord = available_coord[i];
			Enemy* enemy = enemies_[i];
			bool temp = this->AddUnit(coord, enemy);
			if (!temp)
				return false;
			enemy->Move(coord);
		}
	}
	else {
		if (enemy_spawn_.size() < enemies_.size()) {
			for (unsigned int i = 0; i < enemy_spawn_.size(); i++) {
				Coord coord = enemy_spawn_[i];
				Enemy* enemy = enemies_[i];
				bool temp = this->AddUnit(coord, enemy);
				if (!temp)
					return false;
				enemy->Move(coord);
			}
			//find all empty square
			std::vector<Coord> available_coord = {};
			for (int x = 0; x < this->Rows(); x++) {
				for (int y = 0; y < this->Cols(); y++) {
					Coord coord = Coord(x, y);
					Square* square = this->Apply(coord);
					bool available = true;
					for (unsigned int i = 0; i < ally_spawn_.size(); i++) {
						Coord spawn = ally_spawn_[i];
						if (spawn == coord) {
							available = false;
							break;
						}
					}
					if (square->ToString() == "Floor" && available && !square->IsOccupied())
						available_coord.push_back(coord);
				}
			}
			//shuffle the empty square coordinates
			auto rng = std::default_random_engine{};
			rng.seed(seed);
			std::shuffle(std::begin(available_coord), std::end(available_coord), rng);
			//add remaining units to empty squares
			for (unsigned int i = 0; i < enemies_.size() - enemy_spawn_.size(); i++) {
				Coord coord = available_coord[i];
				Enemy* enemy = enemies_[i + enemy_spawn_.size()];
				bool temp = this->AddUnit(coord, enemy);
				if (!temp)
					return false;
				enemy->Move(coord);
			}
		}
		else {
			for (unsigned int i = 0; i < enemy_spawn_.size(); i++) {
				Coord coord = enemy_spawn_[i];
				Enemy* enemy = enemies_[i];
				bool temp = this->AddUnit(coord, enemy);
				if (!temp)
					return false;
				enemy->Move(coord);
			}
		}
	}
	return true;
}

Coord Battlefield::TreasureCoord() {
	for (int x = 0; x < this->Rows(); x++) {
		for (int y = 0; y < this->Cols(); y++) {
			Square* current = this->Apply(Coord(x, y));
			if (current->ToString() == "Treasure")
				return Coord(x, y);
		}
	}
	return Coord(-1, -1);
}

bool Battlefield::OpenTreasure() {
	if (treasures_->empty())
		return false;
	else {
		treasures_->clear();
		return true;
	}
}

std::vector<Enemy*> Battlefield::Enemies() {
	return enemies_;
}

std::vector<Ally*> Battlefield::Allies() {
	return allies_;
}

std::vector<Item>* Battlefield::RemainingTreasure() {
	if (treasures_ == NULL)
		return new std::vector<Item>{};
	else
		return treasures_;
}

bool Battlefield::HasTreasure() {
	return treasures_ != NULL;
}

bool Battlefield::HasEnemies() {
	auto iter = std::find_if(enemies_.begin(), enemies_.end(), [](Enemy* enemy) {
		return enemy->IsAlive();
		});
	return iter != enemies_.end();
}

bool Battlefield::IsClear() {
	return !this->HasEnemies() && !this->HasTreasure();
}

bool Battlefield::Outcome(Unit* attacker, Unit* defender)
{
	std::vector<Coord> area = this->BFS_Attack(attacker->GetLocation(), attacker->GetAttackRange());
	bool inrange = (std::find(area.begin(), area.end(), defender->GetLocation()) != area.end());
	if (attacker->ToString() == defender->ToString() || !inrange)
		return false;
	else
		return true;
}

bool Battlefield::AllyArrive(std::vector<Ally*> army)
{
	if (army[0]->ToString() != "Ally")
		return false;
	else {
		allies_ = army;
		return true;
	}
}

bool Battlefield::EnemyArrive(std::vector<Enemy*> army)
{
	if (army[0]->ToString() != "Enemy")
		return false;
	else {
		enemies_ = army;
		return true;
	}
}

string Battlefield::type()
{
	return "Battlefield";
}


std::vector<Coord> Battlefield::BFS(Coord coord, int range)
{
	std::vector<Coord> queue;
	std::vector<int> dis;
	int front = 0;
	int back = 0;
	int row[4] = { 1, 0,  0,-1 };
	int col[4] = { 0, 1, -1, 0 };
	std::vector<std::vector<int>> map = this->ToInt();

	queue.push_back(coord);
	dis.push_back(0);

	do
	{
		Coord c = queue[front];
		front++;

		for (int i = 0; i < 4; i++)
		{
			if ((c.x() + row[i] > -1) && (c.x() + row[i] < this->Rows()) && (c.y() + col[i] > -1) && (c.y() + col[i] < this->Cols())
				&& (std::find(queue.begin(), queue.end(), Coord(c.x() + row[i], c.y() + col[i])) == queue.end())
				&& (dis[front - 1] + 1 <= range)
				&& (map[(c.y() + col[i])][(c.x() + row[i])] == 0))
			{
				queue.push_back(Coord(c.x() + row[i], c.y() + col[i]));
				if (map[(c.y() + col[i])][(c.x() + row[i])] == 0) 
					dis.push_back(dis[(front - 1)] + 1);
				else 
					dis.push_back(range+1);
				back++;
			}
		}
	} while (front <= back);

	queue.erase(queue.begin());
	return queue;
}

std::vector<Coord> Battlefield::BFS_Attack(Coord coord, int range)
{
  std::vector<Coord> queue;
  std::vector<Coord> result;
  std::vector<int> dis;
  int front = 0;
  int back = 0;
  int row[4] = { 1, 0,  0,-1 };
  int col[4] = { 0, 1, -1, 0 };
  std::vector<std::vector<int>> map = this->ToInt();

  queue.push_back(coord);
  dis.push_back(0);

  do
  {
    Coord c = queue[front];
    front++;

    for (int i = 0; i < 4; i++)
    {
      if ((c.x() + row[i] > -1) && (c.x() + row[i] < this->Rows()) && (c.y() + col[i] > -1) && (c.y() + col[i] < this->Cols())
        && (std::find(queue.begin(), queue.end(), Coord(c.x() + row[i], c.y() + col[i])) == queue.end())
        && (dis[front - 1] + 1 <= range)
        && (map[(c.y() + col[i])][(c.x() + row[i])] <= 0))
      {
        queue.push_back(Coord(c.x() + row[i], c.y() + col[i]));
        if (map[(c.y() + col[i])][(c.x() + row[i])] == 0)
          dis.push_back(dis[(front - 1)] + 1);
        else
        {
          dis.push_back(range + 1);
          result.push_back(Coord(c.x() + row[i], c.y() + col[i]));
        }
        back++;
      }
    }
  } while (front <= back);

  return result;
}

