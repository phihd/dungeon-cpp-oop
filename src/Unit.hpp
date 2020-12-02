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
    Coord location_ = Coord(-1, -1);
    bool hasAttacked_ = true;
    bool hasMoved_ = true;
    int range_ = 0;

public:
    Unit(const string &name, Stat stats, Coord location, int range);

    string GetName() const;

    Stat GetStats() const;

    Coord GetLocation() const;

    vector<Item> GetInventory() const;

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
};


class Ally: public Unit {

public:
    Ally(const string &name, Stat stats, Coord location, int range);

    string ToString();

    string Description();
};

bool operator==(const Ally &a, const Ally &b);


class Enemy: public Unit {

public:
    Enemy(const string &name, Stat stats, Coord location, int range);

    string ToString();

    string Description();
};

bool operator==(const Enemy &a, const Enemy &b);

#endif