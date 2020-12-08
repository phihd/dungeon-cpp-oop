#pragma once
#ifndef STAT_HEADER
#define STAT_HEADER

#include <iostream>
#include <string>

using namespace std;

class Stat {

private:
    int maxHP_;
    int HP_;
    int atk_;
    int def_;
    int crit_;
    int moveRange_;
    int attackRange_;

public:
    Stat(int maxHP, int HP, int atk, int def, int crit, int moveRange, int attackRange);

    int GetMaxHP() const;

    int GetHP() const;

    int GetAtk() const;

    int GetDef() const;

    int GetCrit() const;

    int GetMoveRange() const;

    int GetAttackRange() const;

    Stat& operator+=(const Stat& b);

    Stat& operator-=(const Stat& b);
};

Stat operator+(const Stat &a, const Stat &b);

Stat operator-(const Stat &a, const Stat &b);

#endif