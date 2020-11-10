#include "Item.hpp"
#include "Unit.hpp"

#include <iostream>
#include <string>

using namespace std;

class Player {

private:
    string name_;

public:
    Player(const string &name);

    /*Get the name of the player.*/
    string GetName() const;

    /*Change the name of the player.*/
    string ChangeName(string newName);

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

    string Equip(string itemName, Unit unit);

    string Consume(string itemName, Unit unit);

    string Buy(string itemName, int quantity);

    string Sell(string itemName, int quantity);

    string Loot(string itemName);



};