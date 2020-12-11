#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cmath>

#include "World.hpp"
#include "World.cpp"
#include "Item.hpp"
#include "Stat.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

#define START_SCREEN_STAGE 0
#define STORY_STAGE 1
#define STORE_FUNCTIONALITY_SELECTION_STAGE 2
#define STORE_TRADE_STAGE 3
#define BATTLE_ROOM_STAGE 4

using namespace std;
bool inRange(int num, int small, int big)
{
	return num > small && num < big;
}
//#########################################################################
vector<sf::Texture> textureCollection;
bool buttonClicked(sf::RectangleShape button, sf::Vector2i mousePosition)
{
	return button.getPosition().x <= mousePosition.x && mousePosition.x <= button.getPosition().x + button.getSize().x && button.getPosition().y <= mousePosition.y && mousePosition.y <= button.getPosition().y + button.getSize().y;
}

sf::RectangleShape createButton(float xPos, float yPos, float xSize, float ySize, string texturePath, int opacity = 255, bool centered = false)
{
	sf::Vector2f buttonSize(xSize, ySize);
	sf::RectangleShape button(buttonSize);
	sf::Texture t;
	t.loadFromFile(texturePath);
	button.setFillColor(sf::Color(255, 255, 255, opacity));
	button.setTexture(&textureCollection.emplace_back(t));
	if (centered)
		button.setPosition(xPos - xSize / 2.0f, yPos - ySize / 2.0f);
	else
		button.setPosition(xPos, yPos);
	return button;
}
//##########################################################################

int main()
{
	////////////////////////////////////////////// CLASSES /////////////////////////////////////////////////////

	vector<string> item_name = {"Leather Armor", "Blunt Dagger", "Silk Armor", "Damaged Sword",
								"Heavy Shield", "Tree Branch", "Heavy Sword", "Wooden Bow",
								"Hermit's Ring", "Makeshift Sword", "Assassin's Blade",
								"Warhammer", "Chainmail Armor", "Ring of Protection", "B.F Sword",
								"Trainee's Rapier", "Crossbow", "Steel Armor", "Shield", "Heavy Glaive",
								"Master's Sword", "Master Assassin's Blade", "Vanguard's Armor",
								"Shiny Armor", "Shieldbow", "Serrated Dirk", "Faerie Charm", "Blood Thirster",
								"Vanguard's Shield", "Heavy Crossbow", "Sentinel's Armor", "Overgrowth Armor",
								"Excalibur", "Durandal", "Laevatein", "Blessed Charm", "Assassin's Cloak",
								"Armor of Life", "Small Potion", "Medium Potion", "Large Potion", "Health Flask"};
	Player player = Player("Player 1");
	Game game = Game(player);
	Bot bot = game.bot;

	vector<Battlefield> world = game.CreateWorld();
	std::vector<Rest> rests = game.rests;
	int current_level = 0;
	Battlefield room = world[current_level];

	vector<Unit *> allies = game.allies;
	vector<Unit *> enemies = room.Enemies();

	bot.Enter(&room);
	allies.resize(5);
	player.Recruit(allies);
	player.Enter(&room);
	room.SpawnAlly();

	std::vector<Item> potions = {
		//Item("Sentinel's Armor", "Only legendary heroes wear this", Stat(0, 0, 0, 500, 0, 0, 0), 1200),
		Item("Overgrowth Armor", "The wearer recieves great\nboost of life", Stat(300, 0, 0, 500, 0, 0, 0), 1500),
		Item("Excalibur", "The sword for kings", Stat(0, 0, 3500, 0, 25, 10, 0), 1500),
		//Item("Small Potion", "Small potion with little healing", Stat(0, 20, 0, 0, 0, 0, 0), 20, true),
		Item("Medium Potion", "This gives some nice healing", Stat(0, 75, 0, 0, 0, 0, 0), 50, true),
		//Item("Large Potion", "This heals you nicely", Stat(0, 200, 0, 0, 0, 0, 0), 100, true),
		//Item("Health Flask", "This surely HEALS you", Stat(0, 10000, 0, 0, 0, 0, 0), 250, true),
		//Item("Vanguard's Shield", "High quality shield for\nskilled knights", Stat(0, 0, 0, 120, 0, 0, 0), 500) };
		Item("Heavy Crossbow", "Deadlier version of a crossbow", Stat(0, 0, 1200, 0, 0, 0, 20), 700)};

	for (auto i : potions)
		player.AddItem(i, 5);

	map<Item, int> storeStock;
	storeStock = rests[0].Stock();

	map<Item, int> inventory = player.GetInventory();
	vector<Item> player_inventory;
	for (auto item : inventory)
		player_inventory.push_back(item.first);
	vector<vector<int>> map = room.ToInt();
	string projectPath = filesystem::current_path().generic_string();
	projectPath = projectPath.substr(0, projectPath.find("dungeon-2020-4") + 14);
	string resourcePath = projectPath + "/resource";
	player.startNewTurn();

	/////////////////////////////////////////////////////// UI ///////////////////////////////////////////////////////////
	//Set color
	sf::Color green = sf::Color::Color(133, 255, 161);		// Background     |  0
	sf::Color blue = sf::Color::Color(52, 191, 237);		// Ally           |  1 ->  5
	sf::Color red = sf::Color::Color(219, 33, 26);			// Enemy          | -1 -> -n
	sf::Color grey = sf::Color::Color(110, 110, 110);		// Obstacle       |  6
	sf::Color yellow = sf::Color::Color(255, 226, 135);		// Selector
	sf::Color blue_light = sf::Color::Color(164, 225, 245); // Moveable
	sf::Color orange = sf::Color::Color(255, 168, 54);
	sf::Color orange_dark = sf::Color::Color(87, 62, 30);
	//sf::Color red_light   = sf::Color::Color(255, 134, 130); // Enemy in range
	//sf::Color red_light_2 = sf::Color::Color(224, 216, 192); // Enemy's range

	//Set texture
	sf::Texture texture_attackable, texture_treasure_close, texture_treasure_open, texture_rock, texture_end_turn, texture_items_button_texture;
	vector<sf::Texture> texture_all_items(42);
	texture_attackable.loadFromFile(resourcePath + "/attack.png");
	texture_treasure_close.loadFromFile(resourcePath + "/treasure_close.png");
	texture_treasure_open.loadFromFile(resourcePath + "/treasure_open.png");
	texture_rock.loadFromFile(resourcePath + "/rock.png");
	texture_end_turn.loadFromFile(resourcePath + "/end_turn.png");
	texture_items_button_texture.loadFromFile(resourcePath + "/inventory.png");
	for (unsigned int i = 0; i < 42; i++)
		texture_all_items[i].loadFromFile(resourcePath + "/" + item_name[i] + ".png");

	//Set variables
	float grid_size = 60.f;
	bool is_ally_chosen = false;
	bool is_term_print = false;
	bool need_print = false;
	bool is_show_items = false;
	bool is_item_chosen = false;
	int x_ally = -1;
	int y_ally = -1;
	int x_item = -1;
	int y_item = -1;
	vector<Coord> movable_grids;
	vector<Coord> attack_grids;
	sf::Vector2i mouse_pos;
	sf::Vector2u mouse_pos_grid;
	sf::Vector2i map_size(room.Rows(), room.Cols());
	sf::Vector2i inventory_size(3, 7);

	//Text GUI
	sf::Font font;
	font.loadFromFile(resourcePath + "/Roboto-Medium.ttf");
	sf::Text info1;
	info1.setFont(font);
	info1.setCharacterSize(20);
	info1.setPosition(grid_size * map_size.x + 20.f, 20.f);
	info1.setLineSpacing(1.5f);
	info1.setString("");

	sf::Text info2;
	info2.setFont(font);
	info2.setCharacterSize(20);
	info2.setPosition(grid_size * map_size.x + 20.f, 100.f);
	info2.setLineSpacing(1.5f);
	info2.setString("");

	sf::Text info3;
	info3.setFont(font);
	info3.setCharacterSize(20);
	info3.setPosition(grid_size * map_size.x + 20.f, grid_size * 9 + 30.f);
	info3.setLineSpacing(1.5f);
	info3.setString("");

	sf::Text terminal;
	terminal.setFont(font);
	terminal.setCharacterSize(20);

	terminal.setPosition(20.f, grid_size * map_size.y + 20.f);
	terminal.setLineSpacing(1.5f);
	terminal.setString("");

	//Map GUI
	vector<vector<sf::RectangleShape>> tile_map;
	vector<vector<sf::RectangleShape>> inventory_map;

	tile_map.resize(map_size.x, vector<sf::RectangleShape>());
	inventory_map.resize(inventory_size.x, vector<sf::RectangleShape>());

	for (int x = 0; x < map_size.x; x++)
	{
		tile_map[x].resize(map_size.y, sf::RectangleShape());
		for (int y = 0; y < map_size.y; y++)
		{
			tile_map[x][y].setSize(sf::Vector2f(grid_size, grid_size));
			if (map[y][x] < 0)
				tile_map[x][y].setFillColor(red);
			else if (map[y][x] == 0)
				tile_map[x][y].setFillColor(green);
			else if (inRange(map[y][x], 0, 6))
				tile_map[x][y].setFillColor(blue);
			else if (map[y][x] == 6)
			{
				tile_map[x][y].setFillColor(sf::Color::White);
				tile_map[x][y].setTexture(&texture_rock);
			}
			else if (map[y][x] == 7)
			{
				tile_map[x][y].setFillColor(sf::Color::White);
				tile_map[x][y].setTexture(&texture_treasure_close);
			}
			else if (map[y][x] == 8)
			{
				tile_map[x][y].setFillColor(sf::Color::White);
				tile_map[x][y].setTexture(&texture_treasure_open);
			}
			tile_map[x][y].setOutlineThickness(1.f);
			tile_map[x][y].setOutlineColor(sf::Color::Black);
			tile_map[x][y].setPosition(x * grid_size, y * grid_size);
		}
	}

	for (int x = 0; x < inventory_size.x; x++)
	{
		inventory_map[x].resize(inventory_size.y, sf::RectangleShape());
		for (int y = 0; y < inventory_size.y; y++)
		{
			inventory_map[x][y].setSize(sf::Vector2f(grid_size, grid_size));
			inventory_map[x][y].setFillColor(orange_dark);
			inventory_map[x][y].setOutlineThickness(1.f);
			inventory_map[x][y].setOutlineColor(sf::Color::Black);
			inventory_map[x][y].setPosition(x * grid_size + (map_size.x + 1) * grid_size, y * grid_size + 2 * grid_size);
		}
	}

	//Create the selector
	sf::RectangleShape tile_mouse(sf::Vector2f(grid_size, grid_size));
	tile_mouse.setFillColor(sf::Color::Transparent);
	tile_mouse.setOutlineThickness(1.5f);
	tile_mouse.setOutlineColor(sf::Color::Yellow);

	//Create show items button
	sf::RectangleShape items_button(sf::Vector2f(grid_size, grid_size));
	items_button.setFillColor(sf::Color::White);
	items_button.setOutlineThickness(2.25f);
	items_button.setOutlineColor(sf::Color::Transparent);
	items_button.setPosition(grid_size * (map_size.x - 3), grid_size * map_size.y + 20.f);
	items_button.setTexture(&texture_items_button_texture);

	//Create the end turn button
	sf::RectangleShape end_turn_button(sf::Vector2f(grid_size, grid_size));
	end_turn_button.setFillColor(sf::Color::White);
	end_turn_button.setOutlineThickness(2.25f);
	end_turn_button.setOutlineColor(sf::Color::Transparent);
	end_turn_button.setPosition(grid_size * (map_size.x - 1), grid_size * map_size.y + 20.f);
	end_turn_button.setTexture(&texture_end_turn);

	unsigned int buttonX = 600;
	unsigned int buttonY = 300;
	int windowX = 1680;
	int windowY = 960;
	// A magical number used through out the program to make text/button effects
	int effect_number = 0;
	// Initial stage of the program
	int stage = START_SCREEN_STAGE;
	ifstream ifs(resourcePath + "/story.txt");
	string story((istreambuf_iterator<char>(ifs)),
				 (istreambuf_iterator<char>()));
	string selectedCase = "Buy";
	sf::Event event;

	//Create the window
	sf::RenderWindow window(sf::VideoMode(windowX, windowY), "Dungeons!", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(500);
	sf::Image programIcon;
	programIcon.loadFromFile(resourcePath + "/Warhammer.png"); // File/Image/Pixel
	window.setIcon(programIcon.getSize().x, programIcon.getSize().y, programIcon.getPixelsPtr());

	//////////////////////////////////////////////// RUNNING //////////////////////////////////////////////////////

	while (window.isOpen())
	{
		window.clear();
		textureCollection.clear();
		if (stage == BATTLE_ROOM_STAGE)
		{
			//Update mouse positions
			mouse_pos = sf::Mouse::getPosition(window);
			mouse_pos_grid.x = mouse_pos.x / static_cast<unsigned>(grid_size);
			mouse_pos_grid.y = mouse_pos.y / static_cast<unsigned>(grid_size);

			//Update the selector
			tile_mouse.setPosition(mouse_pos_grid.x * grid_size, mouse_pos_grid.y * grid_size);

			//Text GUI
			stringstream ss1;
			stringstream ss2;
			stringstream ss3;
			stringstream ss_term;

			ss1 << "Room: " << current_level + 1 << "       |       Gold: " << player.GetGold() << "\n";
			if (inRange(mouse_pos_grid.x, -1, map_size.x) && inRange(mouse_pos_grid.y, -1, map_size.y))
				ss1 << "Grid: " << mouse_pos_grid.y << " " << mouse_pos_grid.x << "\n\n";
			else if (inRange(mouse_pos.x, int(items_button.getPosition().x), int(items_button.getPosition().x) + int(items_button.getSize().x)) && inRange(mouse_pos.y, int(items_button.getPosition().y), int(items_button.getPosition().y) + int(items_button.getSize().y)))
			{
				if (!is_show_items)
					ss1 << "Show Inventory\n\n";
				else
					ss1 << "Hide Inventory\n\n";
			}
			else if (inRange(mouse_pos.x, int(end_turn_button.getPosition().x), int(end_turn_button.getPosition().x) + int(end_turn_button.getSize().x)) && inRange(mouse_pos.y, int(end_turn_button.getPosition().y), int(end_turn_button.getPosition().y) + int(end_turn_button.getSize().y)))
				ss1 << "End my turn\n\n";

			//Events
			sf::Event evnt;
			while (window.pollEvent(evnt))
			{
				switch (evnt.type)
				{
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::KeyPressed:
					if (evnt.key.code == sf::Keyboard::Escape)
						window.close();
					break;

				case sf::Event::MouseButtonPressed:
					if (evnt.key.code == sf::Mouse::Left)
						//If the click is in the grid
						if (inRange(mouse_pos_grid.x, -1, map_size.x) && inRange(mouse_pos_grid.y, -1, map_size.y) && inRange(map[mouse_pos_grid.y][mouse_pos_grid.x], 0, 6) && !is_term_print)
						{
							//Remeber the click
							x_ally = mouse_pos_grid.x;
							y_ally = mouse_pos_grid.y;
							is_ally_chosen = true;

							//Add the range
							movable_grids = room.BFS(Coord(x_ally, y_ally), allies[map[y_ally][x_ally] - 1]->GetMoveRange());
							attack_grids = room.BFS_Attack(Coord(x_ally, y_ally), allies[map[y_ally][x_ally] - 1]->GetAttackRange());
							for (Coord i : movable_grids)
								tile_map[i.x()][i.y()].setFillColor(blue_light);
							for (Coord i : attack_grids)
							{
								tile_map[i.x()][i.y()].setFillColor(sf::Color::White);
								tile_map[i.x()][i.y()].setTexture(&texture_attackable);
							}
						}
						//If user click start new turn button
						else if (inRange(mouse_pos.x, int(end_turn_button.getPosition().x), int(end_turn_button.getPosition().x) + int(end_turn_button.getSize().x)) && inRange(mouse_pos.y, int(end_turn_button.getPosition().y), int(end_turn_button.getPosition().y) + int(end_turn_button.getSize().y)))
						{
							//End player turn and bot move random
							if (!room.IsClear())
							{
								bot.startNewTurn();
								for (unsigned int i = 0; i < bot.GetArmy().size(); i++)
								{
									Unit *enemy = bot.GetArmy()[i];
									auto possible_new_locations = room.BFS(enemy->GetLocation(), enemy->GetMoveRange());

									if (!possible_new_locations.empty())
									{
										auto new_location = possible_new_locations[rand() % possible_new_locations.size()];
										bot.Move(enemy, new_location);
									}

									auto possible_ally_locations = room.BFS_Attack(enemy->GetLocation(), enemy->GetAttackRange());
									if (!possible_ally_locations.empty())
									{
										auto new_ally = room.Apply(possible_ally_locations[rand() % possible_ally_locations.size()])->Get();
										bot.Attack(enemy, new_ally);
										player.RefreshArmy();
										bot.RefreshArmy();
									}
								}

								//End bot turn and player turn to move
								if (room.IsLost())
								{
									player.Exit();
									bot.Exit();

									world = game.CreateWorld();
									current_level = 0;
									room = world[current_level];

									allies = game.allies;
									enemies = room.Enemies();

									bot.Enter(&room);
									allies.resize(5);
									player.Recruit(allies);
									player.Enter(&room);
									room.SpawnAlly();

									inventory = player.GetInventory();
									for (auto item : inventory)
										player_inventory.push_back(item.first);
									map = room.ToInt();
								}

								player.startNewTurn();

								//Update room
								map = room.ToInt();
								for (int x = 0; x < map_size.x; x++)
								{
									for (int y = 0; y < map_size.y; y++)
									{
										tile_map[x][y].setTexture(NULL);
										if (map[y][x] < 0)
											tile_map[x][y].setFillColor(red);
										else if (map[y][x] == 0)
											tile_map[x][y].setFillColor(green);
										else if (inRange(map[y][x], 0, 6))
											tile_map[x][y].setFillColor(blue);
										else if (map[y][x] == 6)
										{
											tile_map[x][y].setFillColor(sf::Color::White);
											tile_map[x][y].setTexture(&texture_rock);
										}
										else if (map[y][x] == 7)
										{
											tile_map[x][y].setFillColor(sf::Color::White);
											tile_map[x][y].setTexture(&texture_treasure_close);
										}
										else if (map[y][x] == 8)
										{
											tile_map[x][y].setFillColor(sf::Color::White);
											tile_map[x][y].setTexture(&texture_treasure_open);
										}
									}
								}
							}
							else
							{
								player.Exit();
								bot.Exit();

								if (current_level < 9)
								{
									current_level++;
									room = world[current_level]; //Move to next room
									if (current_level == 3 || current_level == 5 || current_level == 8)
									{
										stage = STORE_FUNCTIONALITY_SELECTION_STAGE;
										for (auto i : allies)
											i->FullHeal();
										switch (current_level)
										{
											case 3:
												storeStock = rests[0].Stock();
												break;
											case 5:
												storeStock = rests[1].Stock();
												break;
											case 8:
												storeStock = rests[2].Stock();
												break;
										}
									}
									bot.Enter(&room);
									player.Enter(&room);
									room.SpawnAlly();

									allies = player.GetArmy();
									enemies = room.Enemies();
								}
								else
								{
									world = game.CreateWorld();
									current_level = 0;
									room = world[current_level];

									allies = game.allies;
									enemies = room.Enemies();

									bot.Enter(&room);
									allies.resize(5);
									player.ReleaseAll();
									player.Recruit(allies);
									player.Enter(&room);
									room.SpawnAlly();
									player.ResetGold();

									player.ClearInventory();
								}

								player.startNewTurn();

								//Update inventory
								inventory = player.GetInventory();
								player_inventory.clear();
								for (auto item : inventory)
									player_inventory.push_back(item.first);

								for (int x = 0; x < inventory_size.x; x++)
									for (int y = 0; y < inventory_size.y; y++)
									{
										inventory_map[x][y].setTexture(NULL);
										inventory_map[x][y].setFillColor(orange_dark);
									}
								int count = 0;
								for (auto i : inventory)
								{
									auto it = find(item_name.begin(), item_name.end(), i.first.GetName());
									inventory_map[count % inventory_size.x][count / inventory_size.x].setFillColor(sf::Color::White);
									inventory_map[count % inventory_size.x][count / inventory_size.x].setTexture(&texture_all_items[it - item_name.begin()]);
									count++;
									if (count > 20)
										break;
								}

								//Update room GUI
								map = room.ToInt();
								for (int x = 0; x < map_size.x; x++)
								{
									for (int y = 0; y < map_size.y; y++)
									{
										tile_map[x][y].setTexture(NULL);
										if (map[y][x] < 0)
											tile_map[x][y].setFillColor(red);
										else if (map[y][x] == 0)
											tile_map[x][y].setFillColor(green);
										else if (inRange(map[y][x], 0, 6))
											tile_map[x][y].setFillColor(blue);
										else if (map[y][x] == 6)
										{
											tile_map[x][y].setFillColor(sf::Color::White);
											tile_map[x][y].setTexture(&texture_rock);
										}
										else if (map[y][x] == 7)
										{
											tile_map[x][y].setFillColor(sf::Color::White);
											tile_map[x][y].setTexture(&texture_treasure_close);
										}
										else if (map[y][x] == 8)
										{
											tile_map[x][y].setFillColor(sf::Color::White);
											tile_map[x][y].setTexture(&texture_treasure_open);
										}
									}
								}
							}
						}
						//If user click show inventory
						else if (inRange(mouse_pos.x, int(items_button.getPosition().x), int(items_button.getPosition().x) + int(items_button.getSize().x)) && inRange(mouse_pos.y, int(items_button.getPosition().y), int(items_button.getPosition().y) + int(items_button.getSize().y)))
						{
							//Change UI of items button
							is_show_items = !is_show_items;
							if (is_show_items)
								items_button.setOutlineColor(sf::Color::Yellow);
							else
								items_button.setOutlineColor(sf::Color::Transparent);

							//Update to the items GUI map
							int count = 0;
							for (auto i : inventory)
							{
								auto it = find(item_name.begin(), item_name.end(), i.first.GetName());
								inventory_map[count % inventory_size.x][count / inventory_size.x].setFillColor(sf::Color::White);
								inventory_map[count % inventory_size.x][count / inventory_size.x].setTexture(&texture_all_items[it - item_name.begin()]);
								count++;
								if (count > 20)
									break;
							}
						}
						//If user click on an item
						else if (inRange(mouse_pos_grid.x, map_size.x, map_size.x + inventory_size.x + 1) && inRange(mouse_pos_grid.y, 1, 2 + inventory_size.y) && is_show_items && inRange(mouse_pos_grid.x - map_size.x - 1 + (mouse_pos_grid.y - 2) * 3, -1, player_inventory.size()))
						{
							//Remeber the click
							x_item = mouse_pos_grid.x;
							y_item = mouse_pos_grid.y;
							is_item_chosen = true;
						}
					break;

				case sf::Event::MouseButtonReleased:
					if (evnt.key.code == sf::Mouse::Left)
						//If enemy is chosen to attack or a cell to move
						if (is_ally_chosen && !is_term_print)
						{
							if (x_ally != -1 && y_ally != -1)
							{
								for (Coord i : movable_grids)
									tile_map[i.x()][i.y()].setFillColor(green);
								for (Coord i : attack_grids)
								{
									tile_map[i.x()][i.y()].setFillColor(red);
									tile_map[i.x()][i.y()].setTexture(NULL);
								}

								if (inRange(mouse_pos_grid.x, -1, map_size.x) && inRange(mouse_pos_grid.y, -1, map_size.y))
								{
									//If player move to a moveable cell
									if (find(movable_grids.begin(), movable_grids.end(), Coord(int(mouse_pos_grid.x), int(mouse_pos_grid.y))) != movable_grids.end())
									{
										ss_term << player.Move(allies[map[y_ally][x_ally] - 1], Coord(mouse_pos_grid.x, mouse_pos_grid.y)) << endl;
										need_print = true;
										map = room.ToInt();
										for (int x = 0; x < map_size.x; x++)
										{
											for (int y = 0; y < map_size.y; y++)
											{
												tile_map[x][y].setTexture(NULL);
												if (map[y][x] < 0)
													tile_map[x][y].setFillColor(red);
												else if (map[y][x] == 0)
													tile_map[x][y].setFillColor(green);
												else if (inRange(map[y][x], 0, 6))
													tile_map[x][y].setFillColor(blue);
												else if (map[y][x] == 6)
												{
													tile_map[x][y].setFillColor(sf::Color::White);
													tile_map[x][y].setTexture(&texture_rock);
												}
												else if (map[y][x] == 7)
												{
													tile_map[x][y].setFillColor(sf::Color::White);
													tile_map[x][y].setTexture(&texture_treasure_close);
												}
												else if (map[y][x] == 8)
												{
													tile_map[x][y].setFillColor(sf::Color::White);
													tile_map[x][y].setTexture(&texture_treasure_open);
												}
											}
										}
									}
									//If player wants to attack an enemy
									else if (map[mouse_pos_grid.y][mouse_pos_grid.x] < 0)
									{
										ss_term << player.Attack(allies[map[y_ally][x_ally] - 1], enemies[abs(map[mouse_pos_grid.y][mouse_pos_grid.x]) - 1]) << endl;
										bot.RefreshArmy();
										player.RefreshArmy();
										need_print = true;

										map = room.ToInt();
										for (int x = 0; x < map_size.x; x++)
										{
											for (int y = 0; y < map_size.y; y++)
											{
												tile_map[x][y].setTexture(NULL);
												if (map[y][x] < 0)
													tile_map[x][y].setFillColor(red);
												else if (map[y][x] == 0)
													tile_map[x][y].setFillColor(green);
												else if (inRange(map[y][x], 0, 6))
													tile_map[x][y].setFillColor(blue);
												else if (map[y][x] == 6)
												{
													tile_map[x][y].setFillColor(sf::Color::White);
													tile_map[x][y].setTexture(&texture_rock);
												}
												else if (map[y][x] == 7)
												{
													tile_map[x][y].setFillColor(sf::Color::White);
													tile_map[x][y].setTexture(&texture_treasure_close);
												}
												else if (map[y][x] == 8)
												{
													tile_map[x][y].setFillColor(sf::Color::White);
													tile_map[x][y].setTexture(&texture_treasure_open);
												}
											}
										}
									}
									//If player wants to open treasure
									else if (inRange(map[mouse_pos_grid.y][mouse_pos_grid.x], 6, 9))
									{
										//Open treasure
										ss_term << player.OpenTreasure(allies[map[y_ally][x_ally] - 1], *(room.Apply(Coord(mouse_pos_grid.x, mouse_pos_grid.y))));

										//Update map
										map = room.ToInt();
										for (int x = 0; x < map_size.x; x++)
										{
											for (int y = 0; y < map_size.y; y++)
											{
												tile_map[x][y].setTexture(NULL);
												if (map[y][x] < 0)
													tile_map[x][y].setFillColor(red);
												else if (map[y][x] == 0)
													tile_map[x][y].setFillColor(green);
												else if (inRange(map[y][x], 0, 6))
													tile_map[x][y].setFillColor(blue);
												else if (map[y][x] == 6)
												{
													tile_map[x][y].setFillColor(sf::Color::White);
													tile_map[x][y].setTexture(&texture_rock);
												}
												else if (map[y][x] == 7)
												{
													tile_map[x][y].setFillColor(sf::Color::White);
													tile_map[x][y].setTexture(&texture_treasure_close);
												}
												else if (map[y][x] == 8)
												{
													tile_map[x][y].setFillColor(sf::Color::White);
													tile_map[x][y].setTexture(&texture_treasure_open);
												}
											}
										}

										//Update the inventory
										inventory = player.GetInventory();
										player_inventory.clear();
										for (auto item : inventory)
											player_inventory.push_back(item.first);

										for (int x = 0; x < inventory_size.x; x++)
											for (int y = 0; y < inventory_size.y; y++)
											{
												inventory_map[x][y].setTexture(NULL);
												inventory_map[x][y].setFillColor(orange_dark);
											}
										int count = 0;
										for (auto i : inventory)
										{
											auto it = find(item_name.begin(), item_name.end(), i.first.GetName());
											inventory_map[count % inventory_size.x][count / inventory_size.x].setFillColor(sf::Color::White);
											inventory_map[count % inventory_size.x][count / inventory_size.x].setTexture(&texture_all_items[it - item_name.begin()]);
											count++;
											if (count > 20)
												break;
										}
										need_print = true;
									}
									//If player moves to other places
									else if (mouse_pos_grid.x != x_ally || mouse_pos_grid.y != y_ally)
									{
										ss_term << "Unit cannot move there!\n\n";
										need_print = true;
									}
								}

								is_ally_chosen = false;
								x_ally = -1;
								y_ally = -1;
							}
						}
						// If player wants to equip/consume an item
						else if (is_item_chosen && !is_term_print)
						{
							if (x_item != -1 && y_item != -1)
							{
								if (inRange(mouse_pos_grid.x, -1, map_size.x) && inRange(mouse_pos_grid.y, -1, map_size.y))
								{
									//If ally is chosen
									if (inRange(map[mouse_pos_grid.y][mouse_pos_grid.x], 0, 6))
									{
										int index = x_item - int(map_size.x) - 1 + (y_item - 2) * 3;
										if (player_inventory[index].IsConsumable())
											ss_term << player.Consume(player_inventory[index], allies[map[mouse_pos_grid.y][mouse_pos_grid.x] - 1]);
										else
											ss_term << player.Equip(player_inventory[index], allies[map[mouse_pos_grid.y][mouse_pos_grid.x] - 1]);
										need_print = true;

										//Update the inventory
										inventory = player.GetInventory();
										player_inventory.clear();
										for (auto item : inventory)
											player_inventory.push_back(item.first);

										for (int x = 0; x < inventory_size.x; x++)
											for (int y = 0; y < inventory_size.y; y++)
											{
												inventory_map[x][y].setTexture(NULL);
												inventory_map[x][y].setFillColor(orange_dark);
											}
										int count = 0;
										for (auto i : inventory)
										{
											auto it = find(item_name.begin(), item_name.end(), i.first.GetName());
											inventory_map[count % inventory_size.x][count / inventory_size.x].setFillColor(sf::Color::White);
											inventory_map[count % inventory_size.x][count / inventory_size.x].setTexture(&texture_all_items[it - item_name.begin()]);
											count++;
											if (count > 20)
												break;
										}
									}
									else
									{
										ss_term << "Items can be equipped to an ally only!\n\n";
										need_print = true;
									}
								}
							}
							is_item_chosen = false;
							x_item = -1;
							y_item = -1;
						}
					break;

				default:
					break;
				}
			}

			//Handle mouse in the grid, or on the buttons or not
			if ((inRange(mouse_pos_grid.x, -1, map_size.x) && inRange(mouse_pos_grid.y, -1, map_size.y)) || (inRange(mouse_pos_grid.x, map_size.x, map_size.x + inventory_size.x + 1) && inRange(mouse_pos_grid.y, 1, 2 + inventory_size.y) && is_show_items))
			{
				if (is_ally_chosen || is_item_chosen)
					tile_mouse.setFillColor(yellow);
				else
					tile_mouse.setFillColor(sf::Color::Transparent);
				tile_mouse.setOutlineColor(sf::Color::Yellow);
			}
			else if (inRange(mouse_pos.x, int(items_button.getPosition().x), int(items_button.getPosition().x) + int(items_button.getSize().x)) && inRange(mouse_pos.y, int(items_button.getPosition().y), int(items_button.getPosition().y) + int(items_button.getSize().y)))
			{
				tile_mouse.setPosition(grid_size * (map_size.x - 3), grid_size * map_size.y + 20.f);
				tile_mouse.setOutlineColor(sf::Color::Yellow);
			}
			else if (inRange(mouse_pos.x, int(end_turn_button.getPosition().x), int(end_turn_button.getPosition().x) + int(end_turn_button.getSize().x)) && inRange(mouse_pos.y, int(end_turn_button.getPosition().y), int(end_turn_button.getPosition().y) + int(end_turn_button.getSize().y)))
			{
				tile_mouse.setPosition(grid_size * (map_size.x - 1), grid_size * map_size.y + 20.f);
				tile_mouse.setOutlineColor(sf::Color::Yellow);
			}
			else
			{
				tile_mouse.setFillColor(sf::Color::Transparent);
				tile_mouse.setOutlineColor(sf::Color::Transparent);
			}

			//Text GUI like terminal
			if (is_term_print && !need_print)
			{
				sf::sleep(sf::seconds(1.25f));
				is_term_print = false;
			}
			if (ss_term.str().length() > 0 && need_print)
			{
				is_term_print = true;
				need_print = false;
			}

			//Text GUI for unit information
			if (inRange(mouse_pos_grid.x, -1, map_size.x) && inRange(mouse_pos_grid.y, -1, map_size.y))
			{
				if (is_ally_chosen)
					ss2 << allies[map[y_ally][x_ally] - 1]->Description() << endl
						<< endl;

				if (inRange(map[mouse_pos_grid.y][mouse_pos_grid.x], 0, 6) && (x_ally != mouse_pos_grid.x || y_ally != mouse_pos_grid.y) && !is_ally_chosen)
					ss2 << allies[map[mouse_pos_grid.y][mouse_pos_grid.x] - 1]->Description();
				if (map[mouse_pos_grid.y][mouse_pos_grid.x] < 0)
					ss2 << enemies[abs(map[mouse_pos_grid.y][mouse_pos_grid.x]) - 1]->Description();
				else if (map[mouse_pos_grid.y][mouse_pos_grid.x] == 7)
					ss2 << "Move near treasure\nto open it\n";
				else if (map[mouse_pos_grid.y][mouse_pos_grid.x] == 8)
					ss2 << "Treasure opened\n";
			}

			//Text GUI for item information
			if (inRange(mouse_pos_grid.x, map_size.x, map_size.x + inventory_size.x + 1) && inRange(mouse_pos_grid.y, 1, 2 + inventory_size.y) && is_show_items && inRange(mouse_pos_grid.x - map_size.x - 1 + (mouse_pos_grid.y - 2) * 3, -1, player_inventory.size()))
			{
				ss3 << player_inventory[mouse_pos_grid.x - int(map_size.x) - 1 + (mouse_pos_grid.y - 2) * 3].FullDescription();
				ss3 << "\nQuantity: " << inventory.find(player_inventory[mouse_pos_grid.x - int(map_size.x) - 1 + (mouse_pos_grid.y - 2) * 3])->second;
			}

			//Prepare the text to print
			info1.setString(ss1.str());
			info2.setString(ss2.str());
			info3.setString(ss3.str());
			terminal.setString(ss_term.str());

			///////////////// Clear and draw /////////////////
			window.clear();

			for (int x = 0; x < map_size.x; x++)
				for (int y = 0; y < map_size.y; y++)
					window.draw(tile_map[x][y]);
			if (is_show_items)
				for (int x = 0; x < inventory_size.x; x++)
					for (int y = 0; y < inventory_size.y; y++)
						window.draw(inventory_map[x][y]);
			window.draw(info1);
			if (!is_show_items)
				window.draw(info2);
			else
				window.draw(info3);
			window.draw(terminal);
			window.draw(end_turn_button);
			window.draw(items_button);
			window.draw(tile_mouse);
		}
		else if (stage == START_SCREEN_STAGE)
		{
			sf::Text dungeonTitle, clickToStart;

			dungeonTitle.setFont(font);
			dungeonTitle.setString("Dungeon Crawler!!!");
			dungeonTitle.setCharacterSize(72);
			dungeonTitle.setStyle(sf::Text::Bold);

			sf::FloatRect titleRect = dungeonTitle.getLocalBounds();
			dungeonTitle.setOrigin(titleRect.left + titleRect.width / 2.0f,
								   titleRect.top + titleRect.height / 2.0f);
			dungeonTitle.setPosition(windowX / 2.0f, windowY * 0.2f);

			clickToStart.setFont(font);
			clickToStart.setString("Click anywhere to start");
			sf::FloatRect ctsRect = clickToStart.getLocalBounds();
			clickToStart.setOrigin(ctsRect.left + ctsRect.width / 2.0f,
								   ctsRect.top + ctsRect.height / 2.0f);
			clickToStart.setPosition(windowX / 2.0f, windowY * 0.8f);

			window.draw(dungeonTitle);
			if (effect_number % 200 > 100)
				window.draw(clickToStart);

			if (window.pollEvent(event))
				if (event.type == sf::Event::Closed)
					window.close();
				else if (event.type == sf::Event::MouseButtonReleased)
				{
					effect_number = 0;
					stage = STORY_STAGE;
				}
		}
		else if (stage == STORY_STAGE)
		{
			sf::Text storyText;
			storyText.setFont(font);
			storyText.setLineSpacing(1.25f);
			storyText.setString(story.substr(0, effect_number / 4));

			sf::FloatRect storyRect = storyText.getLocalBounds();
			storyText.setOrigin(storyRect.left + storyRect.width / 2.0f,
								storyRect.top);
			storyText.setPosition(windowX / 2.0f, windowY * 0.1f);
			window.draw(storyText);
			if (size(story) == size(storyText.getString().toAnsiString()))
				stage = BATTLE_ROOM_STAGE; // Here should be something else
			if (window.pollEvent(event) && event.type == sf::Event::Closed)
				window.close();
		}
		else if (stage == STORE_FUNCTIONALITY_SELECTION_STAGE)
		{
			int opacity = (int)(50 * sin(effect_number / 20.0f) + 205);
			sf::RectangleShape buyButton = createButton(windowX * 0.25f, windowY * 0.25f, (float)buttonX, (float)buttonY, resourcePath + "/Buy_option.png", opacity, true);
			sf::RectangleShape sellButton = createButton(windowX * 0.75f, windowY * 0.25f, (float)buttonX, (float)buttonY, resourcePath + "/Sell_option.png", opacity, true);
			sf::RectangleShape upgradeButton = createButton(windowX * 0.25f, windowY * 0.75f, (float)buttonX, (float)buttonY, resourcePath + "/Upgrade_option.png", opacity, true);
			sf::RectangleShape quitButton = createButton(windowX * 0.75f, windowY * 0.75f, (float)buttonX, (float)buttonY, resourcePath + "/Quit_option.png", opacity, true);
			window.draw(buyButton);
			window.draw(sellButton);
			window.draw(upgradeButton);
			window.draw(quitButton);

			if (window.pollEvent(event))
				if (event.type == sf::Event::Closed)
					window.close();
				else if (event.type == sf::Event::MouseButtonReleased)
				{
					mouse_pos = sf::Mouse::getPosition(window);
					if (buttonClicked(buyButton, mouse_pos))
					{
						stage = STORE_TRADE_STAGE;
						selectedCase = "Buy";
					}
					else if (buttonClicked(sellButton, mouse_pos))
					{
						stage = STORE_TRADE_STAGE;
						selectedCase = "Sell";
					}
					else if (buttonClicked(upgradeButton, mouse_pos))
					{
						stage = STORE_TRADE_STAGE;
						selectedCase = "Upgrade";
					}
					else if (buttonClicked(quitButton, mouse_pos))
					{
						stage = BATTLE_ROOM_STAGE;
						selectedCase = "";
					}
				}
		}
		else if (stage == STORE_TRADE_STAGE)
		{
			sf::RectangleShape backButtonRect = createButton(50, 30, 200, 100, resourcePath + "/stone_arrow.png");
			window.draw(backButtonRect);
			string columnNames = "Name                              Description                                                                               Price    Quantity        Action";
			sf::Text title;
			title.setFont(font);
			title.setStyle(sf::Text::Bold);
			title.setString(columnNames);
			title.setPosition(80, 150);
			window.draw(title);
			float text_location_y = 210;
			// This list is mutable, depends on the functionalities.
			// Buy      => Inventory map from store  map<Item, int>
			// Sell     => Inventory map from player map<Item, int>
			// Upgrade  => Unit from player ???????????
			vector<sf::RectangleShape> actionButtonList;
			std::map<Item, int> inventoryList;
			vector<Unit *> army = player.GetArmy();
			vector<Item> keyList;
			if (selectedCase == "Sell" || selectedCase == "Buy")
			{

				if (selectedCase == "Sell")
					inventoryList = player.GetInventory();
				else
					inventoryList = storeStock;

				for (auto itemset : inventoryList)
				{
					sf::Text name, description, price, quantity;
					keyList.push_back(itemset.first);
					name.setFont(font);
					name.setString(itemset.first.GetName());
					name.setPosition(80, text_location_y);

					description.setFont(font);
					description.setString(itemset.first.GetDescription());
					description.setPosition(400, text_location_y);

					price.setFont(font);
					price.setString(to_string(itemset.first.GetPrice()));
					price.setPosition(1200, text_location_y);

					quantity.setFont(font);
					quantity.setString(to_string(itemset.second));
					quantity.setPosition(1350, text_location_y);

					sf::RectangleShape actionButton = createButton(1450, text_location_y, 190, 60, resourcePath + "/" + selectedCase + ".png");
					actionButtonList.push_back(actionButton);
					window.draw(name);
					window.draw(description);
					window.draw(price);
					window.draw(quantity);
					window.draw(actionButton);

					text_location_y += 60;
				}
			}
			else
			{
				for (auto unit : army)
				{
					sf::Text name, description, price, quantity;
					name.setFont(font);
					name.setString(unit->GetName());
					name.setPosition(80, text_location_y);
					Stat s = unit->GetStats();
					string d = "HP: " + to_string(s.GetHP()) + " ATK: " + to_string(s.GetAtk()) + " Def: " + to_string(s.GetDef()) + " Crit: " + to_string(s.GetCrit());
					description.setFont(font);
					description.setString(d);
					description.setPosition(400, text_location_y);

					price.setFont(font);
					price.setString("2000");
					price.setPosition(1200, text_location_y);

					quantity.setFont(font);
					quantity.setString("N/A");
					quantity.setPosition(1350, text_location_y);

					sf::RectangleShape actionButton = createButton(1450, text_location_y, 190, 60, resourcePath + "/" + selectedCase + ".png");
					actionButtonList.push_back(actionButton);
					window.draw(name);
					window.draw(description);
					window.draw(price);
					window.draw(quantity);
					window.draw(actionButton);

					text_location_y += 60;
				}
			}
			if (window.pollEvent(event))
				if (event.type == sf::Event::Closed)
					window.close();
				else if (event.type == sf::Event::MouseButtonReleased)
				{
					mouse_pos = sf::Mouse::getPosition(window);
					if (buttonClicked(backButtonRect, mouse_pos))
					{
						stage = STORE_FUNCTIONALITY_SELECTION_STAGE;
						selectedCase = "";
					}
					else
						for (auto b : actionButtonList)
							if (buttonClicked(b, mouse_pos))
							{
								int buttonNum = (int)(b.getPosition().y - 210) / 60;
								if (selectedCase == "Sell")
								{
									Item selectedObject = keyList[buttonNum];
									player.Sell(selectedObject, 1, storeStock);

									//Update inventory
									inventory = player.GetInventory();
									player_inventory.clear();
									for (auto item : inventory)
										player_inventory.push_back(item.first);

									for (int x = 0; x < inventory_size.x; x++)
										for (int y = 0; y < inventory_size.y; y++)
										{
											inventory_map[x][y].setTexture(NULL);
											inventory_map[x][y].setFillColor(orange_dark);
										}
									int count = 0;
									for (auto i : inventory)
									{
										auto it = find(item_name.begin(), item_name.end(), i.first.GetName());
										inventory_map[count % inventory_size.x][count / inventory_size.x].setFillColor(sf::Color::White);
										inventory_map[count % inventory_size.x][count / inventory_size.x].setTexture(&texture_all_items[it - item_name.begin()]);
										count++;
										if (count > 20)
											break;
									}
								}
								else if (selectedCase == "Buy")
								{
									Item selectedObject = keyList[buttonNum];
									player.Buy(selectedObject, 1, storeStock);

									//Update inventory
									inventory = player.GetInventory();
									player_inventory.clear();
									for (auto item : inventory)
										player_inventory.push_back(item.first);

									for (int x = 0; x < inventory_size.x; x++)
										for (int y = 0; y < inventory_size.y; y++)
										{
											inventory_map[x][y].setTexture(NULL);
											inventory_map[x][y].setFillColor(orange_dark);
										}
									int count = 0;
									for (auto i : inventory)
									{
										auto it = find(item_name.begin(), item_name.end(), i.first.GetName());
										inventory_map[count % inventory_size.x][count / inventory_size.x].setFillColor(sf::Color::White);
										inventory_map[count % inventory_size.x][count / inventory_size.x].setTexture(&texture_all_items[it - item_name.begin()]);
										count++;
										if (count > 20)
											break;
									}
								}
								else if (selectedCase == "Upgrade")
								{
									//Unit *selectedObject = army[buttonNum];
									player.Upgrade(army[buttonNum], 2000);
									//auto s = selectedObject->GetStats();
									//selectedObject->AdjustStats(Stat(0, (int)(0.25 * s.GetHP()), (int)(0.25 * s.GetAtk()), (int)(0.25 * s.GetDef()), (int)(0.25 * s.GetCrit()), 0, 0));
								}

								// FIXME: Do correct operation accordingly
							}
				}
		}
		else
			window.close();
		window.display();
		effect_number++;
	}

	return 0;
}