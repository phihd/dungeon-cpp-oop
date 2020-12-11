#include "Item.hpp"

#include <iostream>
#include <string>

using namespace std;

Item::Item(const string &name, string description, Stat stat, int price, bool consumable): name_(name), description_(description), stat_(stat), price_(price), consumable_(consumable) {}

string Item::GetName() const {
    return name_;
}

string Item::GetDescription() const {
    return description_;
}

string Item::FullDescription() {
    /* Infinity Edge - 340000 gold
    Equip
    +50 Attack Damge
    -1 Move Range
    "Bigger Fucking Sword"
    */
    string fullDescription = "";
    fullDescription += name_ + " - " + to_string(price_) + " gold\n";
    if (consumable_)
        fullDescription += "Consume\n";
    else
        fullDescription += "Equip\n";
    if (stat_.GetMaxHP() != 0) {
        if (stat_.GetMaxHP() > 0)
            fullDescription += "+";
        fullDescription += to_string(stat_.GetMaxHP()) + " Health\n";
    }
    if (stat_.GetHP() != 0) {
        fullDescription += "Regenerate " + to_string(stat_.GetHP()) + " Health\n";
    }
    if (stat_.GetAtk() != 0) {
        if (stat_.GetAtk() > 0)
            fullDescription += "+";
        fullDescription += to_string(stat_.GetAtk()) + " Attack Damage\n";
    }
    if (stat_.GetDef() != 0) {
        if (stat_.GetDef() > 0)
            fullDescription += "+";
        fullDescription += to_string(stat_.GetDef()) + " Defense\n";
    }
    if (stat_.GetCrit() != 0) {
        if (stat_.GetCrit() > 0)
            fullDescription += "+";
        fullDescription += to_string(stat_.GetCrit()) + " Critical Strike Chance\n";
    }
    if (stat_.GetMoveRange() != 0) {
        if (stat_.GetMoveRange() > 0)
            fullDescription += "+";
        fullDescription += to_string(stat_.GetMoveRange()) + " Move Range\n";
    }
    if (stat_.GetAttackRange() != 0) {
        if (stat_.GetAttackRange() > 0)
            fullDescription += "+";
        fullDescription += to_string(stat_.GetAttackRange()) + " Attack Range\n";
    }
    fullDescription += "\n\"" + GetDescription() + "\"";
    return fullDescription;
}

Stat Item::GetStats() const {
    return stat_;
}

bool Item::IsConsumable() {
    return consumable_;
}

Item& Item::operator=(const Item& b) {
    this->name_ = b.GetName();
    this->description_ = b.GetDescription();
    this->price_ = b.GetPrice();
    this->stat_ = b.GetStats();
    return *this;
}

int Item::GetPrice() const {
    return price_;
}

bool operator==(const Item &a, const Item& b) {
    return a.GetName() == b.GetName();
}

bool operator<(const Item &a, const Item& b) {
    return a.GetName() < b.GetName();
}
