#include "Item.hpp"

#include <iostream>
#include <string>

using namespace std;

Item::Item(const string &name, string description, Stat stat, int price): name_(name), description_(description), stat_(stat), price_(price) {}

string Item::GetName() const {
    return name_;
}

string Item::GetDescription() const {
    return description_;
}

Stat Item::GetStats() const {
    return stat_;
}

Item& Item::operator=(const Item& b) {
    this->name_ = b.GetName();
    this->description_ = b.GetDescription();
    this->price_ = b.GetPrice();
    this->stat_ = b.GetStats();
    return *this;
}

int Item::GetPrice() const {
    return price_;
}

bool operator==(const Item &a, const Item& b) {
    return a.GetName() == b.GetName();
}

bool operator<(const Item &a, const Item& b) {
    return a.GetName() < b.GetName();
}
