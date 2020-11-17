#include "Stat.hpp"
#include "Item.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Unit {

private:
    string name_;
    Stat stats_;
    vector<Item> inventory_;

public:
    Unit(const string &name, Stat stats);

    string GetName();

    Stat GetStats();

    vector<Item> GetInventory();

    void AdjustStats(Stat b);
    
};