#include "Player.hpp"

#include <iostream>
#include <string>

using namespace std;

Player::Player(const string &name): name_(name), hasQuit_(false), gold_(0) {}

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

map<Item, int> Player::GetInventory() const {
    return inventory_;
}

bool Player::HasQuit() {
    return hasQuit_;
}

bool Player::IsAlive() {
    return army_.size() != 0;
}

bool Player::IsDead() {
    return !IsAlive();
}

void Player::quit() {
    hasQuit_ = true;
}

string Player::Examine(Item item) {
    for (auto p: inventory_) {
        Item item_iter = p.first;
        if (item_iter == item)
            return "You are looking closely at the " + item_iter.GetName() + ".\n" + item_iter.GetDescription();
    }
    return "If you want to examine something, you need to have it first.";
}

string Player::Examine(Item item, Ally* unit) {
    for (Item item_iter: unit->GetInventory()) {
        if (item_iter == item)
            return "Unit " + unit->GetName() + " is equipped with " + item_iter.GetName() + ".\n" + item_iter.GetDescription();
    }
    return "Unit " + unit->GetName() + "is not equipped with this item.";
}

bool Player::Has(Item item) {
    for (auto p: inventory_) {
        Item item_iter = p.first;
        if (item_iter == item)
            return true;
    }
    return false;
}

string Player::Inventory() {
    string itemDescription = "";
    if (inventory_.size() > 0) {
        for (auto p: inventory_) {
            Item item_iter = p.first;
            int num = p.second;
            itemDescription += item_iter.GetName() + " x" + to_string(num) + "\n";
        }
        return "You are carrying" + itemDescription + ".";
    }
    return "You are empty-handed.";
}

string Player::Equip(Item item, Ally* unit) {
    for (auto p: inventory_) {
        Item item_iter = p.first;
        if (item_iter == item) {
            unit->Equip(item_iter);
            RemoveItem(item_iter, 1);
            return "Equipped unit " + unit->GetName() + " with " + item_iter.GetName() + ".";
        }
    }
    return "There is no " + item.GetName() + " to equip.";
}

string Player::Unequip(Item item, Ally* unit) {
    for (auto item_iter: unit->GetInventory()) {
        if (item_iter == item) {
            unit->Unequip(item_iter);
            AddItem(item_iter, 1);
            return "Equipped unit " + unit->GetName() + " with " + item_iter.GetName() + ".";
        }
    }
    return "There is no " + item.GetName() + " to equip.";
}

string Player::Consume(Item item, Ally* unit) {
    for (auto p: inventory_) {
        Item item_iter = p.first;
        if (item_iter == item) {
            unit->Consume(item_iter);
            RemoveItem(item_iter, 1);
            return "Consumed " + item_iter.GetName() + " for " + unit->GetName() + ".";
        }
    }
    return "There is no " + item.GetName() + " to consume.";
}

string Player::Buy(Item item, int quantity, map<Item, int> &stock) {
    if (quantity > 0) {
        for (auto p: stock) {
            Item item_iter = p.first;
            if (item_iter == item) {
                int num = p.second;
                if (num >= quantity) {
                    if (gold_ >= item_iter.GetPrice() * quantity) {
                        gold_ -= item_iter.GetPrice() * quantity;
                        AddItem(item_iter, quantity);
                        // Remove bought item_iter from stock
                        if (num - quantity > 0)
                            stock[item_iter] -= quantity;
                        else
                            stock.erase(item_iter);
                        return "Bought " + item.GetName() + " x" + to_string(quantity);
                    }
                    else
                        return "You can not afford  " + to_string(quantity) + " " + item.GetName() + "(s).";
                    
                }
                else
                    return "The shop only has " + num + item.GetName() + "(s) left.";
            } 
        }
        return "There is no" + item.GetName() + "in the stock."; 
    }
    else
        return "Please give a correct quantity.";
    
}

string Player::Sell(Item item, int quantity, map<Item, int> &stock) {
    if (Has(item)) {
        for (auto p: inventory_) {
            Item item_iter = p.first;
            if (item_iter == item) {
                int num = p.second;
                if (num <= quantity) {
                    gold_ += item_iter.GetPrice() * quantity;
                    RemoveItem(item_iter, quantity);
                    // Add items to stock
                    stock[item_iter] += quantity;
                    return "Sold " + item.GetName() + " x" + to_string(quantity);
                }
                else
                    return "You don't have that many " + item.GetName() + " to sell";
                
            }
        }
    }
    return "You don't have this item.";
}

string Player::AddItem(Item item, int quantity) {
    inventory_[item] += quantity;
    return "Added " + to_string(quantity) + " " + item.GetName() + " to the inventory.";
}

string Player::RemoveItem(Item item, int quantity) {
    if (quantity < inventory_[item])
        inventory_[item] += quantity;
    else
        inventory_.erase(item);
    return "Remove " + to_string(quantity) + " " + item.GetName() + " from the inventory.";
}

// string Player::Move(Ally unit, Coord o_location) {
//     unit.Move(o_location);
//     return "Unit moved.";
// }

string Player::Attack(Ally* unit, Enemy* opponent) {
    unit->Attack(opponent);
    return unit->GetName() + " just attacked " + opponent->GetName();
}

string Player::Recruit(Ally* unit)
{
    if (army_.size() >= 5)
        return "Army full!";
    else {
        army_.push_back(unit);
        return unit->GetName() + "recruited.";
    }
}

string Player::Recruit(vector<Ally*> units)
{
    if (army_.empty() && units.size() == 5) {
        army_ = units;
        return "Recruit successful";
    }
    else {
        if (!army_.empty())
            return "Army needs to be empty";
        else
            return "Number of allys exceeds 5";
    }
}

string Player::Release(Ally* ally)
{
    bool temp = false;
    for (unsigned int i = 0; i < army_.size(); i++) {
        Ally* current = army_[i];
        if (current->GetName() == ally->GetName()) {
            temp = true;
        }
    }
    if (temp)
        return ally->GetName() + "released";
    else
        return "Unit not in army";
}

string Player::Move(Ally* ally, Coord new_coord)
{
    bool temp = false;
    for (unsigned int i = 0; i < army_.size(); i++) {
        Ally* current = army_[i];
        if (current->GetName() == ally->GetName()) {
            temp = true;
        }
    }
    if (temp) {
        ally->Move(new_coord);
        return "Move successful";
    }
    else
        return "Unit not in army";
}

Bot::Bot() {}

string Bot::Attack(Enemy* unit, Ally* opponent) {
    unit->Attack(opponent);
    return unit->GetName() + " just attacked " + opponent->GetName();
}

string Bot::Recruit(Enemy* unit)
{
    if (army_.size() >= 5)
        return "Army full!";
    else {
        army_.push_back(unit);
        return unit->GetName() + "recruited.";
    }
}

string Bot::Recruit(vector<Enemy*> units)
{
    for (unsigned int i = 0; i < units.size(); i++) {
        Enemy* unit = units[i];
        army_.push_back(unit);
    }
    return "Recruit successful";
}

string Bot::Release(Enemy* ally)
{
    bool temp = false;
    for (unsigned int i = 0; i < army_.size(); i++) {
        Enemy* current = army_[i];
        if (current->GetName() == ally->GetName()) {
            temp = true;
        }
    }
    if (temp)
        return ally->GetName() + "released";
    else
        return "Unit not in army";
}

string Bot::Move(Enemy* ally, Coord new_coord)
{
    bool temp = false;
    for (unsigned int i = 0; i < army_.size(); i++) {
        Enemy* current = army_[i];
        if (current->GetName() == ally->GetName()) {
            temp = true;
        }
    }
    if (temp) {
        ally->Move(new_coord);
        return "Move successful";
    }
    else
        return "Unit not in army";
}
