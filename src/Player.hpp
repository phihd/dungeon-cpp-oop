#pragma once
#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "Room.hpp"
#include "Room.cpp"
#include "Unit.hpp"
#include "Unit.cpp"     // This is for VSCode, remove if you use visual studio

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Player {

private:
    string name_;
    bool hasQuit_ = false;
    vector<Unit*> army_ = {};
    const int army_max_size_ = 5;
    map<Item, int> inventory_;
    int gold_ = 0;
    Battlefield* battlefield_ = NULL; 

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
    string Examine(Item item, Unit* unit);

    /*Determines if the player has an item.*/
    bool Has(Item item);

    /*Describe items with coresponding quantities in the inventory*/
    string Inventory();

    /*Equip an ally unit with a item*/
    string Equip(Item item, Unit* unit);

    /*Unequip a item from an ally unit*/
    string Unequip(Item item, Unit* unit);

    /*Use a consumable item, e.g., potions for an ally unit*/
    string Consume(Item item, Unit* unit);

    /*Buy an item with a certain quantity*/
    string Buy(Item item, int quantity, map<Item, int> &stock);

    /*Sell an item with a certain quantity*/
    string Sell(Item item, int quantity, map<Item, int> &stock);

    /*Add quantity x item(s) to the inventory*/
    string AddItem(Item item, int quantity);

    string AddItems(vector<Item*> items);

    /*Remove quantity x item(s) in the inventory*/
    string RemoveItem(Item item, int quantity);

    /*Move an ally unit from a location to another one*/
    string Move(Unit unit, Coord* o_location);

    /*Command an ally unit to attack an opponent*/
    string Attack(Unit* unit, Unit* opponent);

    /*Recruit a unit to army*/
    string Recruit(Unit* unit);

    /*Recruit a vector of unit to army, can only be done with empty army and vector has size 5*/
    string Recruit(vector<Unit*> units);

    /*Release a unit from army*/
    string Release(Unit* ally);

    /*Release the whole army*/
    void ReleaseAll();

    /*Move a unit on the map*/
    string Move(Unit* ally, Coord new_coord);

    /*Start a new turn by allowing all unit in the army to have 1 move and 1 attack*/
    string startNewTurn();

    /*Refresh the army - clear death unit*/
    string RefreshArmy();

    /*Return an ally unit by the provided name*/
    Unit* GetUnit(string unitName);

    vector<Unit*> GetArmy();

    void Enter(Battlefield *battlefield);

    void Exit();

    /*Open a treasure through provided coord*/
    string OpenTreasure(Unit *unit, Square treasure);

    void SetBattlefield(Battlefield *Battlefield);

    virtual int getArmyMaxSize() {return army_max_size_;}
};

class Bot: public Player {

public:
    Bot(const string &name);

    void Enter(Battlefield *battlefield);

    void Exit();

    int getArmyMaxSize() {return 1000;}
};

#endif