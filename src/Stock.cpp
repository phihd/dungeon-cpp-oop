#include "Stock.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// TO BE REMOVED

bool Stock::buyItem(Player p, Item i, unsigned int quantity)
{
    auto res = p.Buy(i, quantity, inventory_);
    return true;
}

bool Stock::sellItem(Player p, Item i, unsigned int quantity)
{
    p.Sell(i, quantity, inventory_);
    return true;
}

bool upgradeItem(Player p, Item i, unsigned int price)
{
    return true;
}

bool addItemToStore(Item i, unsigned int quantity)
{
    //auto inv = inventory_;
    //inv[i] += quantity;
    return true;
}