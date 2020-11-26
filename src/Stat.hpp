#pragma once

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

public:
    Stat(int maxHP, int HP, int atk, int def, int crit): maxHP_(maxHP), HP_(HP), atk_(atk), def_(def), crit_(crit) {}

    int GetMaxHP() const;

    int GetHP() const;

    int GetAtk() const;

    int GetDef() const;

    int GetCrit() const;

    Stat& operator+=(const Stat& b);
};

Stat operator+(const Stat &a, const Stat &b);