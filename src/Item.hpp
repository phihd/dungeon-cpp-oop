#include "Stat.hpp"

#include <iostream>
#include <string>

using namespace std;

class Item {

private:
    string name_;
    string description_;
    Stat stat_;
    int price_;

public:
    Item(const string &name, string description, Stat stat, int price);

    string GetName();

    string GetDescription();

    Stat GetStats();

    int GetPrice();

};