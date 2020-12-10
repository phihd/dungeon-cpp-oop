#pragma once
#ifndef ITEM_HEADER
#define ITEM_HEADER

#include "Stat.hpp"
#include "Stat.cpp"     // This is for VSCode, remove if you use visual studio

#include <iostream>
#include <string>

using namespace std;

class Item {

private:
    string name_;
    string description_;
    Stat stat_;
    int price_;
    bool consumable_;

public:
    Item(const string &name, string description, Stat stat, int price, bool consumable = false);

    string GetName() const;

    string GetDescription() const;

    string FullDescription();

    Stat GetStats() const;

    int GetPrice() const;

    bool IsConsumable();

    Item& operator=(const Item& b);

};

bool operator==(const Item &a, const Item& b);

bool operator<(const Item &a, const Item& b);

#endif