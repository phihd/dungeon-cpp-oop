#include "Player.hpp"

#include <iostream>
#include <string>

using namespace std;

Player::Player(const string &name): name_(name) {}

string Player::GetName() const {
    return name_;
}

string Player::ChangeName(string newName) {
    string tmp = name_;
    name_ = newName;
    return tmp + " has changed name to " + name_ + ".";
}

int Player::GetGold() const {
    return gold_;
}

bool Player::HasQuit() {
    return hasQuit_;
}

bool Player::IsAlive() {
    return army_.size() != 0;
}

bool Player::IsDead() {
    return !IsAlive;
}

void Player::quit() {
    hasQuit_ = true;
}

string Player::Examine(string itemName) {
    for (auto p: inventory_) {
        Item item = p.first;
        if (item.GetName() == itemName)
            return "You are looking closely at the " + item.GetName() + ".\n" + item.GetDescription();
    }
    return "If you want to examine something, you need to have it first.";
}

string Player::Examine(string itemName, Unit unit) {
    for (Item item: unit.GetInventory()) {
        if (item.GetName() == itemName)
            return "Unit " + unit.GetName() + " is equipped with " + item.GetName() + ".\n" + item.GetDescription();
    }
    return "Unit " + unit.GetName() + "is not equipped with this item.";
}

bool Player::Has(string itemName) {
    for (auto p: inventory_) {
        Item item = p.first;
        if (item.GetName() == itemName)
            return true;
    }
    return false;
}

string Player::Inventory() {
    string itemDescription = "";
    if (inventory_.size() > 0) {
        for (auto p: inventory_) {
            Item item = p.first;
            int num = p.second;
            itemDescription += item.GetName() + " x" + to_string(num) + "\n";
        }
        return "You are carrying" + itemDescription + ".";
    }
    return "You are empty-handed.";
}

string Player::Equip(string itemName, Unit unit) {
    for (auto p: inventory_) {
        Item item = p.first;
        if (item.GetName() == itemName) {
            // Raise stats
            unit.AdjustStats(item.GetStats());
            // Remove item from inventory
            inventory_.erase(item);
            return "Equipped unit " + unit.GetName() + " with " + item.GetName() + "."; 
        }
    }
    return "There is no " + itemName + " to equip.";

}