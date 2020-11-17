#include "Enemy.hpp"

#include <iostream>
#include <string>

using namespace std;

Enemy::Enemy(const string &name, Stat stats): Unit(name, stats) {}