#include "Room.hpp"

Room::Room() {}

Battlefield::Battlefield(int nrows, int ncols, std::vector<Enemy*> enemies, std::vector<Ally*> allies,
	std::vector<Item>* treasures, std::vector<Coord> spawn) : Grid(nrows, ncols), Room(), enemies_(enemies), allies_(allies), treasures_(treasures), spawn_(spawn) 
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

void Battlefield::AddWall(Coord coord) { this->Update(coord, new Wall); }

void Battlefield::AddTreasure(Coord coord) { this->Update(coord, new Treasure); }

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
			else if (square->ToString() == "Floor")
				row += ".";
			else if (square->ToString() == "Treasure") {
				if (square->IsOpened())
					row += "0";
				else
					row += "1";
			}
			else
				continue;
		}
		result.push_back(row);
	}
	return result;
}

