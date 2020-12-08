#include "Unit.hpp"

#include <iostream>
#include <string>

using namespace std;

Unit::Unit(const string& name, Stat stats) : name_(name), stats_(stats) {}

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

int Unit::GetMoveRange() const {
    return GetStats().GetMoveRange();
}

int Unit::GetAttackRange() const {
    return GetStats().GetAttackRange();
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
    float alpha = (float)100 / (100 + opponent->GetStats().GetDef());
    float dmg = alpha * stats_.GetAtk();
    opponent->AdjustStats(Stat(0, -dmg, 0, 0, 0, 0, 0));
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
    string MoveRange = to_string(GetStats().GetMoveRange());
    string AttackRange = to_string(GetStats().GetAttackRange());
    return " - " + name_ + "\nHP: " + HP + "/" + MaxHP + "\nAttack: " + Atk + "\nDefence: " + Def + "\nCritical strike chance: " + Crit + 
            "\nMove range: " + MoveRange + + "\nAttack range: " + AttackRange;
}

bool operator==(const Unit &a, const Unit &b) {
    return a.GetName() == b.GetName();
}

//----------------------------------------------------------------------------------------------------//

Ally::Ally(const string &name, Stat stats): Unit(name, stats) {}

string Ally::ToString() {
    return "Ally";
}

string Ally::Description() {
    return "Ally" + Unit::Description();
}

bool operator==(const Ally &a, const Ally &b) {
    return a.GetName() == b.GetName();
}


Enemy::Enemy(const string &name, Stat stats): Unit(name, stats) {}

string Enemy::ToString() {
    return "Enemy";
}

string Enemy::Description() {
    return "Enemy" + Unit::Description();
}

bool operator==(const Enemy &a, const Enemy &b) {
    return a.GetName() == b.GetName();
}