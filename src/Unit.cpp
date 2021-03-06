#include "Unit.hpp"

#include <iostream>
#include <string>
#include <random>

using namespace std;

Unit::Unit(const string& name, Stat stats, bool ally) : name_(name), stats_(stats), ally_(ally) {}

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
    return this->GetStats().GetHP() > 0;
}

void Unit::AdjustStats(Stat b) {
    stats_ += b;
}

bool Unit::Equip(Item item) {
    for (unsigned int i = 0; i < inventory_.size(); i++)
        if (inventory_[i] == item || inventory_.size() >= inventory_max_size)
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
    bool isCrit = (rand() % 100) < stats_.GetCrit();
    if (isCrit)
        dmg *= 2;
    opponent->AdjustStats(Stat(0, (int)(-dmg), 0, 0, 0, 0, 0));
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

    string Inventory = "";
    if (!inventory_.empty())
        Inventory += "\n\nCarrying:\n";
    for (int i = 0; i < inventory_.size(); i++)
        Inventory += inventory_[i].GetName() + "\n";

    return " - " + name_ + "\nHP: " + HP + "/" + MaxHP + "\nAttack: " + Atk + "\nDefence: " + Def + "\nCritical Strike Chance: " + Crit + 
            "\nMove Range: " + MoveRange + + "\nAttack Range: " + AttackRange + Inventory;
}

void Unit::FullHeal() {
    stats_.SetHP(stats_.GetMaxHP());
}

bool operator==(const Unit &a, const Unit &b) {
    return a.GetName() == b.GetName();
}

//----------------------------------------------------------------------------------------------------//