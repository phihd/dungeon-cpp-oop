#include "Unit.hpp"

#include <iostream>
#include <string>

using namespace std;

Unit::Unit(const string &name, Stat stats): name_(name), stats_(stats), location_(NULL) {}

string Unit::GetName() const {
    return name_;
}

Stat Unit::GetStats() const {
    return stats_;
}

Coord* Unit::GetLocation() const {
    return location_;
}

vector<Item> Unit::GetInventory() const {
    return inventory_;
}

Coord Unit::GetLocation() const {
    return location_;
}

bool Unit::IsAlive(){
    return (this->GetStats().GetMaxHP() - this->GetStats().GetHP()) == 0;
}

void Unit::AdjustStats(Stat b) {
    stats_ += b;
}

bool Unit::Equip(Item item) {
    for (unsigned int i = 0; i < inventory_.size(); i++)
        if (inventory_[i] == item)
            return false;
    inventory_.push_back(item);
    stats_ += item.GetStats();
    return true;
}

bool Unit::Unequip(Item item) {
    for (unsigned int i = 0; i < inventory_.size(); i++)
        if (inventory_[i] == item) {
            inventory_.erase(inventory_.begin() + i);
            stats_ -= item.GetStats();
            return true;
        }
    return false;
}

void Unit::Consume(Item item) {
    stats_ += item.GetStats();
}

void Unit::Attack(Unit* opponent) {
    int alpha = 100 / (100 + opponent->GetStats().GetDef());
    int dmg = alpha * stats_.GetAtk();
    opponent->AdjustStats(Stat(0, -dmg, 0, 0, 0));
}

void Unit::Move(Coord* o_location) {
    location_ = o_location;
}

string Unit::ToString() {
    return "";
}


Ally::Ally(const string &name, Stat stats): Unit(name, stats) {}

string Ally::ToString() {
    return "Ally";
}


Enemy::Enemy(const string &name, Stat stats, Coord location): Unit(name, stats, location) {}

string Enemy::ToString() {
    return "Enemy";
}