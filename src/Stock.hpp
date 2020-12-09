#pragma once
#ifndef STORE_HEADER
#define STORE_HEADER

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Item.hpp"
#include "Player.hpp"
using namespace std;

// TO BE REMOVED

/* Players can trade objects or upgrade weapons/armors at Store */
class Stock {

private:
    /* Inventory of the store
       When an object is sold out, the object is also removed from the inventory map. 
       When a player sells an Item to Store, the inventory does NOT record the item. 
       This collection always have same keys as priceList. */
    map<Item, int> inventory_;

    /* Pricelist of the store
       When an object is sold out, the object is also removed from the inventory map. 
       When a player sells an Item to Store, the priceList does NOT record the item. 
       This collection always have same keys as inventory. */
    // map<Item, unsigned int> priceList_;

public:
    /* Player buy item from store, return true if the operation is successful
       The store buys the item with the price of Item */
    bool buyItem(Player p, Item i, unsigned int quantity/*, unsigned int price*/);

    /* Player sell item to store, return true if the operation is successful 
       The store sells the item with the price on the priceList*/
    bool sellItem(Player p, Item i, unsigned int quantity/*, unsigned int price*/);

    /* Upgrade item properties at a cost, return true if the operation is successful*/
    bool upgradeItem(Player p, Item i, unsigned int price);
    
    /* Add an item to inventory and priceList */
    bool addItemToStore(Item i, unsigned int quantity/*, unsigned int price*/);
};

#endif