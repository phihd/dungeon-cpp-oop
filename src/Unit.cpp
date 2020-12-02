#include "Unit.hpp"

#include <iostream>
#include <string>

using namespace std;

Unit::Unit(const string& name, Stat stats, Coord location, int range) : name_(name), stats_(stats), location_(location), range_(range) {}

string Unit::GetName() const {
    return name_;
}

Stat Unit::GetStats() const {
    return stats_;
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
    hasAttacked_ = true;
}

void Unit::Move(Coord o_location) {
    location_ = o_location;
    hasMoved_ = true;
}

void Unit::startNewTurn() {
    hasAttacked_ = false;
    hasMoved_ = false;
}

bool Unit::HasMoved() {
    return hasMoved_;
}

bool Unit::HasAttacked() {
    return hasAttacked_;
}

string Unit::Description() {
    string MaxHP = to_string(stats_.GetMaxHP());
    string HP = to_string(GetStats().GetHP());
    string Atk = to_string(GetStats().GetAtk());
    string Def = to_string(GetStats().GetDef());
    string Crit = to_string(GetStats().GetCrit());
    return " - " + name_ + "\nHP: " + MaxHP + "/" + HP + "\nAttack: " + Atk + "\nDefence: " + Def + "\nCritical strike chance: " + Crit;
}

bool operator==(const Unit &a, const Unit &b) {
    return a.GetName() == b.GetName();
}

//----------------------------------------------------------------------------------------------------//

Ally::Ally(const string &name, Stat stats, Coord location, int range): Unit(name, stats, location, range) {}

string Ally::ToString() {
    return "Ally";
}

string Ally::Description() {
    return "Ally\n" + Unit::Description();
}

bool operator==(const Ally &a, const Ally &b) {
    return a.GetName() == b.GetName();
}


Enemy::Enemy(const string &name, Stat stats, Coord location, int range): Unit(name, stats, location, range) {}

string Enemy::ToString() {
    return "Enemy";
}

string Enemy::Description() {
    return "Enemy\n" + Unit::Description();
}

bool operator==(const Enemy &a, const Enemy &b) {
    return a.GetName() == b.GetName();
}