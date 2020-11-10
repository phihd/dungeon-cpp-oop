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
    return tmp + " has changed name to " + name_;
}