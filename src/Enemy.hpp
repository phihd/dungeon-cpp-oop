#ifndef ENEMY_HEADER
#define ENEMY_HEADER

#include "Unit.hpp"

#include <iostream>
#include <string>

using namespace std;

class Enemy: public Unit {

public:
    Enemy(const string &name, Stat stats);
};

#endif