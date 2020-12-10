#include "Square.hpp"
Square::Square(){}

const bool Square::IsObstacle() { return false; }

const bool Square::IsOccupied() { return false; }

void Square::Clear() {}

Unit* Square::Get() { return NULL; }

bool Square::Put(Unit* unit) { return false; }

bool Square::Place(std::vector<Item>* treasure) { return false; }

bool Square::IsOpened() { return false; }

bool Square::Open() { return false; }

std::string Square::PrintTreasure() { return ""; }

std::string Square::PrintUnit() { return ""; }

std::string Square::ToString() { return ""; }

/*******************************************************************************************************************/

Wall::Wall() : Square() {}

const bool Wall::IsObstacle() { return true; }

const bool Wall::IsOccupied() { return false; }

void Wall::Clear() {}

Unit* Wall::Get() { return unit_; }

bool Wall::Put(Unit* unit) { (void)unit;  return false; }

bool Wall::Place(std::vector<Item>* treasure) { return false; }

bool Wall::IsOpened() { return false; }

bool Wall::Open() { return false; }

std::string Wall::PrintTreasure() { return "Not Treasure Square"; }

std::string Wall::PrintUnit() { return "Not Floor"; }

std::string Wall::ToString() { return "Wall"; }

/*******************************************************************************************************************/

Floor::Floor() : Square() {}

const bool Floor::IsObstacle() { return false; }

const bool Floor::IsOccupied() { return unit_ != NULL; }

void Floor::Clear() { unit_ = NULL; }

Unit* Floor::Get() { return unit_; }

bool Floor::Put(Unit* unit) {
	if (!IsOccupied()) {
		unit_ = unit;
		return true;
	}
	else {
		return false;
	}
}

bool Floor::Place(std::vector<Item>* treasure) { return false; }

bool Floor::IsOpened() { return false; }

bool Floor::Open() { return false; }

std::string Floor::PrintTreasure() { return "Not Treasure Square"; }

std::string Floor::PrintUnit() {
	if (unit_ != NULL) {
		return unit_->GetName();
	}
	else {
		return "Empty Square";
	}
}

std::string Floor::ToString() { return "Floor"; }

/*******************************************************************************************************************/

Treasure::Treasure() : Square() {}

const bool Treasure::IsObstacle() { return true; }

const bool Treasure::IsOccupied() { return false; }

void Treasure::Clear() {}

Unit* Treasure::Get() { return unit_; }

bool Treasure::Put(Unit* unit) { (void)unit;  return false; }

bool Treasure::Place(std::vector<Item>* treasure) { treasure_ = treasure; return treasure_ != NULL; }

bool Treasure::IsOpened() { return treasure_ == NULL; }

std::vector<Item>* Treasure::Open() {
	if (!this->IsOpened()) {
		std::vector<Item>* result = treasure_;
		treasure_ = NULL;
		return result;
	}
	else {
		return new std::vector<Item>{};
	}
}

std::string Treasure::ToString() { return "Treasure"; }

std::string Treasure::PrintTreasure() {
	if (treasure_ != NULL) {
		std::string result;
		size_t n = treasure_->size();
		for (unsigned int i = 0; i < n; i++) {
			Item item = treasure_->operator[](i);
			result += item.GetName() + "\n";
		}
		return result;
	}
	else {
		return "Empty Treasure";
	}
}

std::string Treasure::PrintUnit() { return "Not Floor"; }
