#pragma once
#ifndef STATE_HEADER
#define STATE_HEADER

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "Player.hpp"
#include "World.hpp"
#include "StateStack.hpp"
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Network.hpp>
#include <SFML\Audio.hpp>
using namespace std;
/* Context holds contents to be rendered. (???) */
struct Context
{
    Context(sf::RenderWindow &window //,
                                     // TextureHolder &textures,
                                     // FontHolder &fonts,
                                     // Player &player
    );
    sf::RenderWindow *window;
    // TextureHolder *textures;
    // FontHolder *fonts;
    // Player *player;
};

/* The game state (abstract) */
class State
{

private:
public:
    explicit State(StateStack &stack, Context context /*string stateName*/);
};

/* Game state, triggered when player calls game menu. */
class MenuState : public State
{
public:
    MenuState(StateStack &stack, Context context);
    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event &event);

private:
    World mWorld;
    Player &mPlayer; // Maybe unnecessary
};

/* Title state, the first screen of the game. */
class TitleState : public State
{
public:
    TitleState(StateStack &stack, Context context);
    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event &event);

private:
    sf::Sprite mBackgroundSprite; // No background image yet
    sf::Text mText;
};

/* Game state, triggered when player is in the dungeon */
class MapState : public State
{
public:
    MapState(StateStack &stack, Context context);
    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event &event);

private:
    World mWorld;
    Player &mPlayer; // Maybe unnecessary
};

/* Game state, triggered when player is in a room */
class RoomState : public State // Three possible room types, trade/fight/rest
{
public:
    RoomState(StateStack &stack, Context context);
    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event &event);

private:
    World mWorld;
    Player &mPlayer; // Maybe unnecessary
};

#endif