#include "Stat.hpp"

#include <iostream>
#include <string>

using namespace std;

Stat::Stat(int maxHP, int HP, int atk, int def, int crit): maxHP_(maxHP), HP_(HP), atk_(atk), def_(def), crit_(crit) {}

Stat& Stat::operator+=(const Stat &b) {
    this->atk_ += b.atk_;
    this->crit_ += b.crit_;
    this->def_ += b.def_;
    this->HP_ += b.HP_;
    this->maxHP_ += b.maxHP_;
    return *this;
}

Stat operator+(const Stat &a, const Stat &b) {
    return Stat(a) += b;
}