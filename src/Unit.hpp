#pragma once
#ifndef UNIT_HEADER
#define UNIT_HEADER

#include "Item.hpp"
#include "Item.cpp"     // This is for VSCode, remove if you use visual studio
#include "Coord.hpp"
#include "Coord.cpp"    // This is for VSCode, remove if you use visual studio

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Unit {

private:
    string name_;
    Stat stats_;
    vector<Item> inventory_;
    const int inventory_max_size = 4;
    Coord location_ = Coord(-1, -1);
    bool hasAttacked_ = true;
    bool hasMoved_ = true;
    bool ally_;

public:
    Unit(const string &name, Stat stats, bool ally = true);

    string GetName() const;

    Stat GetStats() const;

    Coord GetLocation() const;

    vector<Item> GetInventory() const;

    int GetMoveRange() const;

    int GetAttackRange() const;

    bool IsAlive();

    void AdjustStats(Stat b);

    bool Equip(Item item);

    bool Unequip(Item item);

    void Consume(Item item);

    void Attack(Unit* opponent);

    void Move(Coord o_location);
    
    virtual string ToString() {return "";   };

    virtual string Description();

    void startNewTurn();

    bool HasMoved();

    bool HasAttacked();

    bool isAlly() { return ally_; };

    void FullHeal();

    void ClearInventory() { inventory_.clear(); }

};

bool operator==(const Unit& a, const Unit& b);

#endif