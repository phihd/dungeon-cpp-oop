#pragma once
#ifndef UNIT_HEADER
#define UNIT_HEADER

#include "Item.hpp"
//#include "Square.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Unit {

private:
    string name_;
    Stat stats_;
    vector<Item> inventory_;
    //Floor location_;

public:
    Unit(const string &name, Stat stats);

    string GetName() const;

    Stat GetStats() const;

    //Floor GetLocation() const;

    vector<Item> GetInventory() const;

    void AdjustStats(Stat b);

    bool Equip(Item item);

    bool Unequip(Item item);

    void Consume(Item item);

    void Attack(Unit opponent);

    //void Move(Floor o_location);
    
};

#endif