#pragma once
#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "Item.hpp"
#include "Unit.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Player {

private:
    string name_;
    bool hasQuit_;
    vector<Ally*> army_ = {};
    map<Item, int> inventory_;
    int gold_;

public:
    Player(const string &name);

    /*Get the name of the player.*/
    string GetName() const;

    /*Change the name of the player.*/
    string ChangeName(string newName);

    int GetGold() const;

    map<Item, int> GetInventory() const;

    /*Determines if the player has indicated a desire to quit the game.*/
    bool HasQuit();

    /*Determines if the player is alive, i.e., still control at least one alive unit*/
    bool IsAlive();

    /*Determines if the player is dead, i.e., the whole army has been destroyed*/
    bool IsDead();

    /*Signals that the player wants to quit the game. Returns a description of what happened within 
    *the game as a result*/
    void quit();

    /*Examine a certain item in inventory, return the item's description.*/
    string Examine(Item item);

    /*Examine a certain item in an ally unit, return the item's description.*/
    string Examine(Item item, Ally* unit);

    /*Determines if the player has an item.*/
    bool Has(Item item);

    /*Describe items with coresponding quantities in the inventory*/
    string Inventory();

    /*Equip an ally unit with a item*/
    string Equip(Item item, Ally* unit);

    /*Unequip a item from an ally unit*/
    string Unequip(Item item, Ally* unit);

    /*Use a consumable item, e.g., potions for an ally unit*/
    string Consume(Item item, Ally* unit);

    /*Buy an item with a certain quantity*/
    string Buy(Item item, int quantity, map<Item, int> &stock);

    /*Sell an item with a certain quantity*/
    string Sell(Item item, int quantity, map<Item, int> &stock);

    /*Add quantity x item(s) to the inventory*/
    string AddItem(Item item, int quantity);

    /*Remove quantity x item(s) in the inventory*/
    string RemoveItem(Item item, int quantity);

    /*Move an ally unit from a location to another one*/
    string Move(Ally unit, Coord* o_location);

    /*Command an ally unit to attack an opponent*/
    string Attack(Ally* unit, Enemy* opponent);

    /*Recruit a unit to army*/
    string Recruit(Ally* unit);

    /*Recruit a vector of unit to army, can only be done with empty army and vector has size 5*/
    string Recruit(vector<Ally*> units);

    /*Release a unit from army*/
    string Release(Ally* ally);

    /*move a unit on the map*/
    string Move(Ally* ally, Coord new_coord);
};

class Bot {

private:
    vector<Enemy*> army_ = {};

public:
    Bot();

    /*Move an ally unit from a location to another one*/
    //string Move(Ally unit, Coord o_location);

    /*Command an ally unit to attack an opponent*/
    string Attack(Enemy* unit, Ally* opponent);

    /*Recruit a unit to army*/
    string Recruit(Enemy* unit);

    /*Recruit a vector of unit to army*/
    string Recruit(vector<Enemy*> units);

    /*Release a unit from army*/
    string Release(Enemy* ally);

    /*move a unit on the map*/
    string Move(Enemy* ally, Coord new_coord);
};

#endif