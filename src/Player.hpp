#include "Item.hpp"
#include "Unit.hpp"
#include "Ally.hpp"
#include "Item.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Player {

private:
    string name_;
    bool hasQuit_;
    vector<Ally> army_;
    map<Item, int> inventory_;
    int gold_;

public:
    Player(const string &name);

    /*Get the name of the player.*/
    string GetName() const;

    /*Change the name of the player.*/
    string ChangeName(string newName);

    int GetGold() const;

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
    string Examine(string itemName);

    /*Examine a certain item in a unit, return the item's description.*/
    string Examine(string itemName, Unit unit);

    /*Determines if the player has an item.*/
    bool Has(string itemName);

    /*Describe items with coresponding quantities in the inventory*/
    string Inventory();

    /*Equip a unit with a item*/
    string Equip(string itemName, Unit unit);

    /*Use a consumable item, e.g., potions*/
    string Consume(string itemName, Unit unit);

    /*Buy an item with a certain quantity*/
    string Buy(string itemName, int quantity);

    /*Sell an item with a certain quantity*/
    string Sell(string itemName, int quantity);

    /*Loot an item, i.e., add the item to the inventory*/
    string Loot(string itemName);



};