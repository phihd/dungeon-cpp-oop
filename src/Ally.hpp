#include "Unit.hpp"

#include <iostream>
#include <string>

using namespace std;

class Ally: public Unit {

public:
    Ally(const string &name, Stat stats);
};