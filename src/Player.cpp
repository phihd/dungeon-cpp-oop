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

string Player::Examine(Item item, Unit* unit) {
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

string Player::Equip(Item item, Unit* unit) {
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

string Player::Unequip(Item item, Unit* unit) {
    for (auto item_iter: unit->GetInventory()) {
        if (item_iter == item) {
            unit->Unequip(item_iter);
            AddItem(item_iter, 1);
            return "Equipped unit " + unit->GetName() + " with " + item_iter.GetName() + ".";
        }
    }
    return "There is no " + item.GetName() + " to equip.";
}

string Player::Consume(Item item, Unit* unit) {
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

string Player::Attack(Unit* unit, Unit* opponent) {
    if (unit->HasAttacked())
        return "Unit already attacked in this turn.";
    unit->Attack(opponent);
    return unit->GetName() + " just attacked " + opponent->GetName();
}

string Player::Recruit(Unit* unit) {
    if (army_.size() >= 5)
        return "Army full!";
    army_.push_back(unit);
    return unit->GetName() + "recruited.";
}

string Player::Recruit(vector<Unit*> units) {
    if (army_.empty() && units.size() == army_max_size_) {
        army_ = units;
        return "Recruit successful";
    }
    if (!army_.empty())
        return "Army needs to be empty";
    return "Number of allys exceeds 5";
}

string Player::Release(Unit* ally) {
    for (unsigned int i = 0; i < army_.size(); i++) {
        Unit* current = army_[i];
        if (*current == *ally) {
            return ally->GetName() + "released";
        }
    }
    return "Unit not in army";
}

string Player::Move(Unit* ally, Coord new_coord) {
    for (unsigned int i = 0; i < army_.size(); i++) {
        Unit* current = army_[i];
        if (*current == *ally) {
            if (current->HasMoved())
                return "Unit already made its move for this turn.";
            if (!battlefield_->MoveUnit(new_coord, ally))
                return ally->GetName() + " can't move to this location.";
            Coord old_location = ally->GetLocation();
            if (old_location == new_coord)
                return "You don't wanna move to the same place (this is only for debug).";
            ally->Move(new_coord);
            return "Move successful from " + old_location.ToString() + " to " + ally->GetLocation().ToString();
        }
    }
    return "Unit not in army";
}

string Player::startNewTurn() {
    for (unsigned int i = 0; i < army_.size(); i++) {
        Unit* unit = army_[i];
        unit->startNewTurn();
    }
    return "Started a new turn";
}

Unit* Player::GetUnit(string unitName) {
    for (int i = 0; i < army_.size(); i++)
        if (army_[i]->GetName() == unitName)
            return army_[i];
    return NULL;
}

vector<Unit*> Player::GetArmy() {
    return army_;
}

void Player::Enter(Battlefield *battlefield) {
    battlefield_ = battlefield;
}

void Player::Exit(Battlefield *battlefield) {
    battlefield_ = NULL;
}


Bot::Bot(const string &name): Player(name) {}