#include "Unit.hpp"

#include <iostream>
#include <string>

using namespace std;

Unit::Unit(const string &name, Stat stats): name_(name), stats_(stats) {}

string Unit::GetName() const {
    return name_;
}

Stat Unit::GetStats() const {
    return stats_;
}

vector<Item> Unit::GetInventory() const {
    return inventory_;
}

void Unit::AdjustStats(Stat b) {
    stats_ += b;
}