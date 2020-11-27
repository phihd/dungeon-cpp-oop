#pragma once
#ifndef UNIT_HEADER
#define UNIT_HEADER

#include "Item.hpp"
#include "World.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Unit {

private:
    string name_;
    Stat stats_;
    vector<Item> inventory_;
    Coord location_;

public:
    Unit(const string &name, Stat stats, Coord location);

    string GetName() const;

    Stat GetStats() const;

    Coord GetLocation() const;

    vector<Item> GetInventory() const;

    void AdjustStats(Stat b);

    bool Equip(Item item);

    bool Unequip(Item item);

    void Consume(Item item);

    void Attack(Unit opponent);

    void Move(Coord o_location);
    
};


class Ally: public Unit {

public:
    Ally(const string &name, Stat stats, Coord location);
};


class Enemy: public Unit {

public:
    Enemy(const string &name, Stat stats, Coord location);
};

#endif