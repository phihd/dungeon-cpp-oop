#pragma once
#ifndef GAME_HEADER
#define GAME_HEADER

#include "Player.hpp"
//#include "Player.cpp"	// This is for VSCode, remove if you use visual studio

#include <algorithm>
#include <random>
#include<time.h>
#include <map>

class Game {
public:
	Game(Player player);
	//World map
	//Blank map 
	/*
							  {"....................",
							   "....................",
							   "....................",
							   "....................",
							   "....................",
							   "....................",
							   "....................",
							   "....................",
							   "....................",
							   "....................",
							   "....................",
							   "...................." };
	*/
	/*Sketch of world: Rest0 -> Stage1 -> Stage2 -> Rest1 -> Stage3 -> Boss1 -> Rest2 -> Stage5 -> Stage6 -> Boss2 
					-> Rest3 -> Stage8 -> Stage9 -> Final Boss;
	*/
	//Designs of Stage1
	std::vector<string> lv1_1 = { "##..........##.....c",
								  ".##.........##......",
								  "..##........##......",
								  "...##.......##..####",
								  "....##...##.........",
								  ".....#####..........",
								  "......##.....##.....",
								  "...........#####....",
								  "####..##..##...##...",
								  "......##........##..",
								  "......##.........##.",
								  "......##..........##" };

	std::vector<string> lv1_2 = { "............##.....c",
								  "............##......",
								  "......##....##......",
								  "......##....##..####",
								  "......##.......##...",
								  ".....##.......##....",
								  "....##.......##.....",
								  "...##.......##......",
								  "####..##....##......",
								  "......##....##......",
								  "......##............",
								  "......##............" };

	std::vector<string> lv1_3 = { "............##.....c",
								  "............##......",
								  ".....##..#####......",
								  ".....##.........####",
								  ".....##..####..##...",
								  ".....##.......##....",
								  "....##.......##.....",
								  "...##..####..##.....",
								  "####.........##.....",
								  "......#####..##.....",
								  "......##............",
								  "......##............" };
	std::vector<std::vector<string>> lv1_designs = { lv1_1, lv1_2, lv1_3 };

	//Designs of Stage2

	std::vector<string> lv2_1 = { ".##...##c...##...##.",
								  "..##...##..##...##..",
								  "...##..##..##..##...",
								  "....##........##....",
								  ".....####..####.....",
								  "....................",
								  "....................",
								  ".....####..####.....",
								  "....##........##....",
								  "...##..##..##..##...",
								  "..##...##..##...##..",
								  ".##...##....##...##." };

	std::vector<string> lv2_2 = { ".##......##......##.",
								  "..##.....##.....##..",
								  "...##....##....##...",
								  "..#####......#####..",
								  ".........##......#..",
								  "....#####........#..",
								  "..#........#####....",
								  "..#......##.........",
								  "..#####..##..#####..",
								  "...##....##...c##...",
								  "..##.....##.....##..",
								  ".##..............##." };

	std::vector<string> lv2_3 = { ".##..............##.",
								  "..##..###.c###..##..",
								  "...##....##....##...",
								  "....##.##.....##....",
								  ".....##.............",
								  "......##............",
								  "............##......",
								  ".............##.....",
								  "....##.....##.##....",
								  "...##....##....##...",
								  "..##..###..###..##..",
								  ".##..............##." };
	std::vector<std::vector<string>> lv2_designs = { lv2_1, lv2_2, lv2_3 };

	//Designs of Stage3
	std::vector<string> lv3_1 = { ".........##.........",
								  ".........##c........",
								  "..################..",
								  "....................",
								  "..#######..#######..",
								  "....................",
								  "....................",
								  "..#######..#######..",
								  "....................",
								  "..################..",
								  ".........##.........",
								  ".........##........." };

	std::vector<string> lv3_2 = { "##................##",
								  "..##............##..",
								  "....##........##....",
								  "......##....##......",
								  "..####....##..#####.",
								  "....................",
								  "....................",
								  "..####....##c.#####.",
								  "......##....##......",
								  "....##........##....",
								  "..##.....##.....##..",
								  "##......####......##" };

	std::vector<string> lv3_3 = { ".........##.........",
								  "..##.....##.....##..",
								  ".##....######....##.",
								  "..##.##..##c.##.##..",
								  "...##....##....##...",
								  "....................",
								  "....................",
								  "...##....##....##...",
								  "..##.##..##..##.##..",
								  ".##....######....##.",
								  "..##.....##.....##..",
								  ".........##........." };
	std::vector<std::vector<string>> lv3_designs = { lv3_1, lv3_2, lv3_3 };

	//Designs of Boss1
	std::vector<string> lv4 = {	  "...##############...",
								  "...##..........##...",
								  "...##..........##...",
								  "...##..........##...",
								  "...##..........##...",
								  "...#####....#####...",
								  "######........######",
								  "....##........##....",
								  "c...................",
								  "....##........##....",
								  "######........######",
								  "...................." };
	std::vector<std::vector<string>> lv4_designs = { lv4 };

	//Designs of Stage5
	std::vector<string> lv5_1 = { "............##.....c",
								  "......##....##......",
								  "..##..##....##......",
								  "..##..##....##......",
								  "..##..##............",
								  "............########",
								  "########............",
								  "............##..##..",
								  "......##....##..##..",
								  "......##....##..##..",
								  "......##....##......",
								  "......##............" };

	std::vector<string> lv5_2 = { "............##.....c",
								  "............##......",
								  "............##......",
								  "......########..####",
								  "..##............##..",
								  "..##........######..",
								  "..######........##..",
								  "..##............##..",
								  "####..########......",
								  "......##............",
								  "......##............",
								  "......##............" };

	std::vector<string> lv5_3 = { "..........##....##..",
								  "................##..",
								  "..........##...c##..",
								  "...###############..",
								  "...##...#..#........",
								  "...##...............",
								  "...............##...",
								  "........#..#...##...",
								  "..###############...",
								  "..##....##..........",
								  "..##................",
								  "..##....##.........." };
	std::vector<std::vector<string>> lv5_designs = { lv5_1, lv5_2, lv5_3 };

	//Designs of Stage6
	std::vector<string> lv6_1 = { ".........##.........",
								  ".......##..##.......",
								  ".....##......##.....",
								  "...##..........##...",
								  ".##..............##.",
								  "....................",
								  "....................",
								  ".##..............##.",
								  "...##..........##...",
								  ".....##......##.....",
								  ".......##..##.......",
								  ".........##........." };

	std::vector<string> lv6_2 = { ".........##.........",
								  ".......##..##.......",
								  ".....##......##.....",
								  "...##....##....##...",
								  ".##......##......##.",
								  "...........#####....",
								  "....#####...........",
								  ".##......##......##.",
								  "...##....##....##...",
								  ".....##......##.....",
								  ".......##..##.......",
								  ".........##........." };

	std::vector<string> lv6_3 = { ".........##.........",
								  ".......##..##.......",
								  ".....##......##.....",
								  "...##....##....##...",
								  ".##......##..##..##.",
								  "...........##.......",
								  ".......##...........",
								  ".##..##..##......##.",
								  "...##....##....##...",
								  ".....##......##.....",
								  ".......##..##.......",
								  ".........##........." };
	std::vector<std::vector<string>> lv6_designs = { lv6_1, lv6_2, lv6_3 };

	//Designs of Boss2
	std::vector<string> lv7 = {   ".....#...c....#.....",
								  ".....#........#.....",
								  ".....###....###.....",
								  ".......#....#.......",
								  "..######....######..",
								  "..#..............#..",
								  "..#..............#..",
								  "..######....######..",
								  ".......#....#.......",
								  ".....###....###.....",
								  ".....#........#.....",
								  ".....#........#....." };
	std::vector<std::vector<string>> lv7_designs = { lv7 };

	//Designs of Stage8
	std::vector<string> lv8_1 = { "....##c.....#....#..",
								  ".#..######..#....#..",
								  ".#............####..",
								  ".#######....#.......",
								  ".......#....#####...",
								  ".......#............",
								  "..######.....#####..",
								  "..#....#.....#...#..",
								  "..#..............#..",
								  ".....###....###..#..",
								  ".....#........#..#..",
								  ".....#........#....." };

	std::vector<string> lv8_2 = { "####............####",
								  "#....##..##..##....#",
								  ".....##..##..##.....",
								  "..####...##...####..",
								  "....................",
								  "...##############...",
								  ".....#...c....#.....",
								  ".....##......##.....",
								  "....................",
								  "....####....####....",
								  "....##........##....",
								  "....##........##...." };

	std::vector<string> lv8_3 = { "...############....#",
								  "........##.........#",
								  "#.......##c........#",
								  "#...##..#######....#",
								  "#...######.........#",
								  "#.......##..........",
								  "#...........##......",
								  "######..#...########",
								  "........#...........",
								  "...######....##...##",
								  ".....##......#.....#",
								  ".....##......#######" };
	std::vector<std::vector<string>> lv8_designs = { lv8_1, lv8_2, lv8_3 };

	//Designs of Stage9
	std::vector<string> lv9_1 = { "..##......c.....##..",
								  "..##............##..",
								  "....................",
								  "....................",
								  "..##............##..",
								  "..##............##..",
								  "....................",
								  "....................",
								  "..##............##..",
								  "..##............##..",
								  ".....##......##.....",
								  ".....#........#....." };

	std::vector<string> lv9_2 = { "####.....c......####",
								  "####.....##.....####",
								  "......########......",
								  ".........##.........",
								  "#####..........#####",
								  "#####..........#####",
								  ".........##.........",
								  "......########......",
								  "##.......##.......##",
								  "##................##",
								  ".....##......##.....",
								  ".....#........#....." };

	std::vector<string> lv9_3 = { "..##.....c......##..",
								  "..##.....##.....##..",
								  ".......######.......",
								  ".....##########.....",
								  "..##...######...##..",
								  "####.....##.....####",
								  "####.....##.....####",
								  "..##...######...##..",
								  ".....##########.....",
								  "....................",
								  "..#####......#####..",
								  ".....#........#....." };
	std::vector<std::vector<string>> lv9_designs = { lv9_1, lv9_2, lv9_3 };

	//Designs of FinalBoss
	std::vector<string> lv10 = { "......########......",
								  "...####......####...",
								  "####...........#####",
								  "##................##",
								  "##................##",
								  "##................##",
								  "####............####",
								  "...####......####...",
								  "#....##......##....#",
								  "#######......#######",
								  "....................",
								  "...................." };
	std::vector<std::vector<string>> lv10_designs = { lv10 };
	std::vector< std::vector<std::vector<string>>> designs = { lv1_designs, lv2_designs, lv3_designs, lv4_designs,
					lv5_designs, lv6_designs, lv7_designs, lv8_designs, lv9_designs, lv10_designs };
	std::vector<std::vector<Coord>> spawns = {
		{Coord(1, 10), Coord(2, 10), Coord(3, 10), Coord(6, 11), Coord(6, 12)},
		{Coord(1, 5), Coord(1, 6), Coord(1, 7), Coord(2, 5), Coord(2, 6)},
		{Coord(1, 5), Coord(1, 6), Coord(1, 7), Coord(2, 5), Coord(2, 6)},
		{Coord(7, 12), Coord(8, 12), Coord(9, 12), Coord(10, 12), Coord(11, 12)},
		{Coord(1, 10), Coord(2, 10), Coord(3, 10), Coord(6, 11), Coord(6, 12)},
		{Coord(3, 6), Coord(1, 6), Coord(1, 7), Coord(1, 5), Coord(1, 8)},
		{Coord(9, 12), Coord(10, 12), Coord(8, 12), Coord(11, 12), Coord(12, 12)},
		{Coord(9, 12), Coord(10, 12), Coord(8, 12), Coord(11, 12), Coord(12, 12)},
		{Coord(9, 12), Coord(10, 12), Coord(8, 12), Coord(11, 12), Coord(12, 12)},
		{Coord(9, 12), Coord(10, 12), Coord(8, 12), Coord(11, 12), Coord(12, 12)}
	};
	std::vector<std::vector<Coord>> boss_spawns = {
		{Coord(10, 3), Coord(9, 6), Coord(12, 6), Coord(5, 9), Coord(15, 9)}, {Coord(10, 5), Coord(11, 5)}, {Coord(11, 5)} };

	//Player
	Bot bot = Bot("Bot 1");

	//Units for player:
	Ally* paladin = new Ally("Paladin", Stat(400, 400, 100, 75, 0, 6, 1));
	Ally* knight = new Ally("Knight", Stat(300, 300, 75, 75, 0, 5, 1));
	Ally* mage = new Ally("Mage", Stat(200, 200, 50, 25, 50, 4, 5));
	Ally* archer = new Ally("Archer", Stat(200, 200, 50, 50, 0, 4, 4));
	Ally* sniper = new Ally("Heavy Archer", Stat(200, 200, 100, 50, 0, 3, 5));
	Ally* valkyrie = new Ally("Valkyrie", Stat(300, 300, 100, 80, 0, 5, 1));
	Ally* assassin = new Ally("Assassin", Stat(300, 300, 175, 90, 0, 7, 1));
	Ally* wizard = new Ally("Grand Wizard", Stat(200, 200, 120, 50, 0, 3, 5));
	Ally* guardian = new Ally("Guardian", Stat(500, 500, 50, 200, 0, 4, 1));
	Ally* swordman = new Ally("Sword man", Stat(300, 300, 100, 60, 0, 6, 1));

	//Enemies
	std::vector<std::vector<Enemy*>> enemies = {
		{
			//lv1
		new Enemy("Scout 1", Stat(75, 75, 150, 50, 0, 5, 5)),
		new Enemy("Scout 2", Stat(75, 75, 150, 50, 0, 5, 5)),
		new Enemy("Scout 3", Stat(75, 75, 150, 50, 0, 5, 5)),
		new Enemy("Scout 4", Stat(75, 75, 150, 50, 0, 5, 5)),
		new Enemy("City Patrol 1", Stat(100, 100, 100, 100, 0, 4, 1)),
		new Enemy("City Patrol 2", Stat(100, 100, 100, 100, 0, 4, 1)),
		new Enemy("City Patrol 3", Stat(100, 100, 100, 100, 0, 4, 1)),
		new Enemy("City Patrol 4", Stat(100, 100, 100, 100, 0, 4, 1)),
		new Enemy("Thief 1", Stat(50, 50, 75, 25, 0, 7, 2)),
		new Enemy("Thief 2", Stat(50, 50, 75, 25, 0, 7, 2)),
		},
		{
			//lv2
		new Enemy("City Guard 1", Stat(150, 150, 100, 100, 0, 4, 1)),
		new Enemy("City Guard 2", Stat(150, 150, 100, 100, 0, 4, 1)),
		new Enemy("City Guard 3", Stat(150, 150, 100, 100, 0, 4, 1)),
		new Enemy("City Archer 1", Stat(100, 100, 200, 100, 0, 6, 2)),
		new Enemy("City Archer 2", Stat(100, 100, 200, 100, 0, 6, 2)),
		new Enemy("City Archer 3", Stat(100, 100, 200, 100, 0, 6, 2)),
		new Enemy("City Patrol 1", Stat(100, 100, 100, 100, 0, 4, 1)),
		new Enemy("City Patrol 2", Stat(100, 100, 100, 100, 0, 4, 1)),
		new Enemy("City Patrol 3", Stat(100, 100, 100, 100, 0, 4, 1)),
		new Enemy("City Patrol 4", Stat(100, 100, 100, 100, 0, 4, 1)),
		},
		{
			//lv3
		new Enemy("City Guard 1", Stat(150, 150, 100, 100, 0, 4, 1)),
		new Enemy("City Guard 2", Stat(150, 150, 100, 100, 0, 4, 1)),
		new Enemy("City Guard 3", Stat(150, 150, 100, 100, 0, 4, 1)),
		new Enemy("City Chevalier 1", Stat(200, 200, 150, 100, 0, 6, 2)),
		new Enemy("City Chevalier 2", Stat(200, 200, 150, 100, 0, 6, 2)),
		new Enemy("City Chevalier 3", Stat(200, 200, 150, 100, 0, 6, 2)),
		new Enemy("City Chevalier 4", Stat(200, 200, 150, 100, 0, 6, 2)),
		new Enemy("City Archer 1", Stat(100, 100, 200, 100, 0, 6, 2)),
		new Enemy("City Archer 2", Stat(100, 100, 200, 100, 0, 6, 2)),
		new Enemy("City Archer 3", Stat(100, 100, 200, 100, 0, 6, 2)),
		},
		{
			//boss1
		new Enemy("The Gate Keeper", Stat(500, 500, 300, 200, 0, 4, 1)),
		new Enemy("Gate Keeper's Minion 1", Stat(250, 250, 200, 150, 0, 4, 1)),
		new Enemy("Gate Keeper's Minion 2", Stat(250, 250, 200, 150, 0, 4, 1)),
		new Enemy("Gate Keeper's Minion 3", Stat(250, 250, 200, 150, 0, 4, 1)),
		new Enemy("Gate Keeper's Minion 4", Stat(250, 250, 200, 150, 0, 4, 1)),
		},
		{
			//lv5
		new Enemy("Outer Knight 1", Stat(250, 250, 150, 150, 0, 4, 1)),
		new Enemy("Outer Knight 2", Stat(250, 250, 150, 150, 0, 4, 1)),
		new Enemy("Outer Knight 3", Stat(250, 250, 150, 150, 0, 4, 1)),
		new Enemy("Outer Knight 4", Stat(250, 250, 150, 150, 0, 4, 1)),
		new Enemy("Outer Archer 1", Stat(200, 200, 200, 100, 0, 5, 5)),
		new Enemy("Outer Archer 2", Stat(200, 200, 200, 100, 0, 5, 5)),
		new Enemy("Outer Archer 3", Stat(200, 200, 200, 100, 0, 5, 5)),
		new Enemy("Outer Archer 4", Stat(200, 200, 200, 100, 0, 5, 5)),
		new Enemy("Outer Guardian", Stat(400, 400, 100, 250, 0, 4, 1)),
		new Enemy("Outer Paladin", Stat(350, 350, 200, 200, 0, 5, 1)),
		},
		{
			//lv6
		new Enemy("Knight Sentinel 1", Stat(300, 300, 150, 150, 0, 4, 1)),
		new Enemy("Knight Sentinel 2", Stat(300, 300, 150, 150, 0, 4, 1)),
		new Enemy("Knight Sentinel 3", Stat(300, 300, 150, 150, 0, 4, 1)),
		new Enemy("Knight Sentinel 4", Stat(300, 300, 150, 150, 0, 4, 1)),
		new Enemy("Knight Sentinel 5", Stat(300, 300, 150, 150, 0, 4, 1)),
		new Enemy("Archer Sentinel 1", Stat(200, 200, 150, 150, 10, 5, 1)),
		new Enemy("Archer Sentinel 2", Stat(200, 200, 150, 150, 10, 5, 1)),
		new Enemy("Archer Sentinel 3", Stat(200, 200, 150, 150, 10, 5, 1)),
		new Enemy("Archer Sentinel 4", Stat(200, 200, 150, 150, 10, 5, 1)),
		new Enemy("Archer Sentinel 5", Stat(200, 200, 150, 150, 10, 5, 1)),
		},
		{
			//boss2
		new Enemy("Hand of the King", Stat(1500, 1500, 250, 250, 0, 6, 2)),
		new Enemy("The Grand Bishop", Stat(1000, 1000, 300, 150, 0, 7, 7)),
		},
		{
			//lv8
		new Enemy("Royal Guard 1", Stat(300, 300, 150, 150, 0, 4, 1)),
		new Enemy("Royal Guard 2", Stat(300, 300, 150, 150, 0, 4, 1)),
		new Enemy("Royal Guard 3", Stat(300, 300, 150, 150, 0, 4, 1)),
		new Enemy("Royal Guard 4", Stat(300, 300, 150, 150, 0, 4, 1)),
		new Enemy("Royal Archer 1", Stat(200, 200, 150, 150, 10, 5, 1)),
		new Enemy("Royal Archer 2", Stat(200, 200, 150, 150, 10, 5, 1)),
		new Enemy("Royal Archer 3", Stat(200, 200, 150, 150, 10, 5, 1)),
		new Enemy("Royal Archer 4", Stat(200, 200, 150, 150, 10, 5, 1)),
		new Enemy("Royal Paladin", Stat(500, 500, 200, 150, 0, 6, 2)),
		new Enemy("Royal Mage", Stat(200, 200, 250, 150, 0, 6, 6))
		},
		{
			//lv9
		new Enemy("Elite Royal Guard 1", Stat(400, 400, 200, 200, 0, 4, 1)),
		new Enemy("Elite Royal Guard 2", Stat(400, 400, 200, 200, 0, 4, 1)),
		new Enemy("Elite Royal Guard 3", Stat(400, 400, 200, 200, 0, 4, 1)),
		new Enemy("Elite Royal Guard 4", Stat(400, 400, 200, 200, 0, 4, 1)),
		new Enemy("Elite Royal Archer 1", Stat(200, 200, 250, 150, 10, 5, 1)),
		new Enemy("Elite Royal Archer 2", Stat(200, 200, 250, 150, 10, 5, 1)),
		new Enemy("Elite Royal Archer 3", Stat(200, 200, 250, 150, 10, 5, 1)),
		new Enemy("Elite Royal Archer 4", Stat(200, 200, 250, 150, 10, 5, 1)),
		new Enemy("Elite Royal Paladin", Stat(500, 500, 300, 150, 0, 6, 2)),
		new Enemy("Elite Royal Mage", Stat(200, 200, 350, 150, 0, 6, 6))
		},
		{
			//final boss
		new Enemy("The King", Stat(2000, 2000, 800, 600, 25, 1, 1)),
		}
	};

	//Items
	
	std::vector<Item> lv1_items = {
		Item("Leather Armor", "A light and reliable piece of armor", Stat(0, 0, 0, 50, 0, 0, 0), 100),
		Item("Blunt Dagger", "A blunt dagger. Can it cut through anything?", Stat(0, 0, 20, 0, 0, 0, 0), 50),
		Item("Silk Armor", "Very light but not a lot protection", Stat(0, 0, 0, 10, 0, 0, 0), 50),
		Item("Damaged Sword", "A damaged sword. Is it reliable?", Stat(0, 0, 40, 0, 0, 0, 0), 100),
		Item("Heavy Shield", "A lot of protection, but so heavy...", Stat(0, 0, 0, 90, 0, -2, 0), 250),
		Item("Tree Branch", "Not exactly a weapon, but it might do the job?", Stat(0, 0, 10, 0, 0, 0, 0), 50),
		Item("Heavy Sword", "Deals nice damge, but so heavy to carry around.", Stat(0, 0, 90, 0, 0, -1, 0), 250),
		Item("Wooden Bow", "A normal wooden bow", Stat(0, 0, 30, 0, 0, 0, 1), 100),
		Item("Hermit's Ring", "People say this ring curse those who wear it", Stat(20, 0, 10, 20, 0, -2, 0), 150),
		Item("Makeshift Sword", "You can tell it's not crafted by a blacksmith", Stat(0, 0, 35, 0, 0, 0, 0), 100)
	};
	std::vector<Item> lv2_items = {
		Item("Assassin's Blade", "Swift and deadly", Stat(0, 0, 80, 0, 0, 0, 0), 300),
		Item("Warhammer", "This can do some damage", Stat(0, 0, 90, 0, 0, 0, 0), 300),
		Item("Chainmail Armor", "Some nice armor", Stat(0, 0, 0, 70, 0, 0, 0), 300),
		Item("Ring of Protection", "Some says it can protect its wearer through many battle", Stat(50, 0, 0, 50, 0, 0, 0), 400),
		Item("B.F Sword", "Big f sword. Deals nice damage but very heavy", Stat(0, 0, 120, 0, 0, -1, 0), 450),
		Item("Trainee's Rapier", "An good rapier", Stat(0, 0, 60, 0, 0, 0, 0), 200),
		Item("Crossbow", "A deadlier version of a bow", Stat(0, 0, 60, 0, 0, 0, 1), 250),
		Item("Steel Armor", "Some nice armor", Stat(0, 0, 0, 100, 0, 0, 0), 450),
		Item("Shield", "Some shield for protection", Stat(0, 0, 0, 50, 0, 0, 0), 200),
		Item("Heavy Glaive", "Doubles the damge with 2 blades but heavy", Stat(0, 0, 150, 0, 0, -1, 0), 500)
	};
	std::vector<Item> lv3_items = {
		Item("Master's Sword", "A fine sword wielded by a weapon master", Stat(0, 0, 200, 0, 0, 0, 0), 700),
		Item("Master Assassin's Hidden Blade", "Swift, deadly and can attack from a far", Stat(0, 0, 180, 0, 0, 0, 2), 700),
		Item("Vanguard's Armor", "High quality armor for skilled knights", Stat(0, 0, 0, 200, 0, 0, 0), 700),
		Item("Shiny Armor", "You look good while not dying", Stat(0, 0, 0, 150, 0, 0, 0), 600),
		Item("Shieldbow", "Some defense and some offense", Stat(0, 0, 0, 100, 50, 0, 0), 700),
		Item("Serrated Dirk", "This can deal some ugly wound to your enemies", Stat(0, 0, 150, 0, 0, 0, 0), 600),
		Item("Faerie Charm", "You get a guardian angel by your side", Stat(100, 0, 50, 100, 0, 0, 0), 700),
		Item("Blood Thirster", "It protects, it attacks", Stat(70, 0, 175, 0, 0, 0, 0), 750),
		Item("Vanguard's Shield", "High quality shield for skilled knights", Stat(0, 0, 0, 120, 0, 0, 0), 500),
		Item("Heavy Crossbow", "Deadlier version of a crossbow", Stat(0, 0, 100, 0, 0, 0, 1), 700)
	};
	std::vector<Item> lv4_items = {
		Item("Sentinel's Armor", "Only legendary heroes wear this", Stat(0, 0, 0, 500, 0, 0, 0), 1200),
		Item("Overgrowth Armor", "The wearer recieves great boost of life", Stat(300, 0, 0, 500, 0, 0, 0), 1500),
		Item("Excalibur", "The sword for kings", Stat(0, 0, 500, 0, 25, 0, 0), 1500),
		Item("Durandal", "The sword of a legendary paladin", Stat(0, 0, 450, 250, 0, 0, 0), 1500),
		Item("Laevatein", "Deadly and mischievous", Stat(0, 0, 500, 0, 0, 1, 2), 1500),
		Item("Blessed Charm", "It blesses its wearer", Stat(200, 0, 300, 300, 0, 1, 1), 1800),
		Item("Assassin's Cloak", "Move so fast no one can catch you", Stat(0, 0, 0, 200, 0, 3, 2), 1000),
		Item("Armor of Life", "Protection comes in many form", Stat(800, 0, 0, 0, 0, 0, 0), 1000)
	};
	std::vector<Item> potions = {
		Item("Small Potion", "Small potion with little healing", Stat(0, 20, 0, 0, 0, 0, 0), 20),
		Item("Medium Potion", "This gives some nice healing", Stat(0, 75, 0, 0, 0, 0, 0), 50),
		Item("Large Potion", "This heals you nicely", Stat(0, 200, 0, 0, 0, 0, 0), 100),
		Item("Health Flask", "This surely HEALS you", Stat(0, 10000, 0, 0, 0, 0, 0), 250) };
	std::vector<std::vector<Item>> items = { lv1_items, lv2_items, lv3_items, lv4_items };
	
	//Make game
	std::vector<Battlefield> CreateWorld();

	//bool CreateGame();
	

private:
};
#endif
