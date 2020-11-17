#include "Item.hpp"

#include <iostream>
#include <string>

using namespace std;

Item::Item(const string &name, string description, Stat stat, int price): name_(name), description_(description), stat_(stat), price_(price) {}

string Item::GetName() {
    return name_;
}

string Item::GetDescription() {
    return description_;
}

Stat Item::GetStats() {
    return stat_;
}

int Item::GetPrice() {
    return price_;
}
