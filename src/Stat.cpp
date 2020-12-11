#include "Stat.hpp"

#include <iostream>
#include <string>

using namespace std;

Stat::Stat(int maxHP, int HP, int atk, int def, int crit, int moveRange, int attackRange): maxHP_(maxHP), HP_(HP), atk_(atk), 
                                                                                            def_(def), crit_(crit), moveRange_(moveRange), attackRange_(attackRange) {}

Stat& Stat::operator+=(const Stat &b) {
    this->atk_ += b.atk_;
    this->crit_ += b.crit_;
    this->def_ += b.def_;
    this->HP_ += b.HP_;
    this->maxHP_ += b.maxHP_;
    if (b.maxHP_ > 0)
        this->HP_ += b.maxHP_;

    this->HP_ = max(this->HP_, 0);
    this->HP_ = min(this->maxHP_, this->HP_);
    this->maxHP_ = max(this->maxHP_, 0);
    return *this;
}

Stat& Stat::operator-=(const Stat &b) {
    this->atk_ -= b.atk_;
    this->crit_ -= b.crit_;
    this->def_ -= b.def_;
    this->HP_ -= b.HP_;
    this->maxHP_  -= b.maxHP_;

    this->HP_ = max(this->HP_, 0);
    this->HP_ = min(this->maxHP_, this->HP_);
    this->maxHP_ = max(this->maxHP_, 0);
    return *this;
}

int Stat::GetMaxHP() const {
    return maxHP_;
}

int Stat::GetHP() const
{
    return HP_;
}

int Stat::GetDef() const {
    return def_;
}

int Stat::GetCrit() const
{
    return crit_;
}

int Stat::GetAtk() const {
    return atk_;
}

int Stat::GetMoveRange() const {
    return moveRange_;
}

int Stat::GetAttackRange() const {
    return attackRange_;
}

void Stat::SetHP(int HP) {
    HP_ = HP;
}

Stat operator+(const Stat &a, const Stat &b) {
    return Stat(a) += b;
}

Stat operator-(const Stat &a, const Stat &b) {
    return Stat(a) -= b;
}
