#pragma once
#ifndef STATESTACK_HEADER
#define STATESTACK_HEADER

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Network.hpp>
#include <SFML\Audio.hpp>
using namespace std;
// TODO: Redesign the whole stack
class StateStack : private sf::NonCopyable
{
public:
    enum Action
    {
        Push,
        Pop,
        Clear,
    };

public:
    explicit StateStack(State::Context context);
    template <typename T>
    void registerState(States::ID stateID);
    void update(sf::Time dt);
    void draw();
    void handleEvent(const sf::Event &event);
    void pushState(States::ID stateID);
    void popState();
    void clearStates();
    bool isEmpty() const;

private:
    State::Ptr createState(States::ID stateID);
    void applyPendingChanges();

private:
    struct PendingChange
    {
        // ... Action action;
        States::ID stateID;
    };

private:
    vector<State::Ptr> mStack;
    vector<PendingChange> mPendingList;
    State::Context mContext;
    map<States::ID, function<State::Ptr()>> mFactories;
};