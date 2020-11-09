#include "Stat.hpp"

#include <iostream>
#include <string>

using namespace std;

class Unit {

private:
    string name_;
    Stat stats_;

public:
    Unit(const string &name, Stat stats);
    
};