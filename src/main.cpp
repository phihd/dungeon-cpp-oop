#include<iostream>
#include<sstream>
#include<vector>
#include<algorithm>

#include "World.hpp"

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Network.hpp>
#include <SFML\Audio.hpp>

bool inRange(int num, int small, int big)
{
	if (num > small && num < big) return true;
	return false;
}

int main()
{
	////////////////////////////////////////////// CLASSES /////////////////////////////////////////////////////
	Ally* paladin = new Ally("Paladin", Stat(200, 200, 100, 75, 0, 1, 5));
	Ally* knight = new Ally("Knight", Stat(150, 150, 75, 75, 0, 2, 3));
	Ally* mage = new Ally("Mage", Stat(100, 100, 50, 25, 0, 3, 4));
	Ally* archer = new Ally("Archer", Stat(100, 100, 50, 0, 0, 4, 20));
	Ally* heavy_archer = new Ally("Heavy Archer", Stat(100, 100, 100, 0, 0, 5, 1));

	Enemy* melee = new Enemy("Melee", Stat(100, 100, 25, 50, 0, 1, 3));
	Enemy* melee1 = new Enemy("Melee1", Stat(100, 100, 25, 50, 0, 1, 4));
	Enemy* range = new Enemy("Range", Stat(100, 100, 40, 20, 0, 4, 2));
	Enemy* range1 = new Enemy("Range1", Stat(100, 100, 40, 20, 0, 4, 3));
	Enemy* canon = new Enemy("Canon", Stat(200, 200, 70, 70, 0, 5, 1));

	vector<Unit*> allies_u{ paladin, knight, mage, archer, heavy_archer };
	vector<Ally*> allies{ paladin, knight, mage, archer, heavy_archer };
	vector<Unit*> enemies_u{ melee, melee1, range, range1, canon };
	vector<Enemy*> enemies{ melee, melee1, range, range1, canon };

	Player player = Player("Player 1");
	player.Recruit(allies_u);
	Bot bot = Bot("Bot 1");
	bot.Recruit(enemies_u);
	std::vector<Item>* treasure_list = new std::vector<Item>{ Item("B.F Sword", "big fucking sword", Stat(0, 0, 50, 0, 0, 0, 0), 1300), 
		Item("Infinity Edge", "bigger fucking sword", Stat(0, 0, 125, 0, 0, 0, 0), 1300) };
	
	Battlefield room(22, 14, enemies, allies, treasure_list);
	player.Enter(&room);
	bot.Enter(&room);
	std::vector<string> design{".....###..1.###.....",
							   "...###........###...",
							   "...#.####...#...#...",
							   "##.....##...##....##",
							   "##..........########",
							   "##....##....##....##",
							   "##....##....###..###",
							   "##....##..........##",
							   "########....########",
							   "......##....##......",
							   "............##....##",
							   "......##..........##" };
	room.FromString(design);
	room.SetAllySpawn(std::vector<Coord>{Coord(1, 12), Coord(1, 11), Coord(2, 12), Coord(2, 11), Coord(3, 11)});
	room.SpawnAlly();
	room.SpawnEnemy();

	std::vector<std::vector<int>> map = room.ToInt();
	
	player.startNewTurn();

	/////////////////////////////////////////////////////// UI ///////////////////////////////////////////////////////////
	//Set color
	sf::Color green       = sf::Color::Color(133, 255, 161); // Background     |  0
	sf::Color blue        = sf::Color::Color( 52, 191, 237); // Ally           |  1 ->  5
	sf::Color red         = sf::Color::Color(219,  33,  26); // Enemy          | -1 -> -n
	sf::Color grey        = sf::Color::Color(110, 110, 110); // Obstacle       |  6
	sf::Color orange      = sf::Color::Color(255, 168,  54); // Open Treasure  |  7
	sf::Color orange_dark = sf::Color::Color(189, 107,   0); // Close Treasure |  8
	sf::Color yellow      = sf::Color::Color(255, 226, 135); // Selector
	sf::Color blue_light  = sf::Color::Color(164, 225, 245); // Moveable
	sf::Color blue_dark   = sf::Color::Color( 24,  91, 125); // Moved
	sf::Color red_light   = sf::Color::Color(255, 134, 130); // Enemy in range
	sf::Color red_light_2 = sf::Color::Color(224, 216, 192); // Enemy's range
	sf::Color temp;

	//Set texture
	sf::Texture attackable, treasure_close, treasure_open, rock;
	attackable.loadFromFile("../../../font/main.png");
	treasure_close.loadFromFile("../../../font/treasure_close.png");
	treasure_open.loadFromFile("../../../font/treasure_open.png");
	rock.loadFromFile("../../../font/rock.png");

	//Set variables
	float grid_size = 60.f;
	bool is_chosen = false;
	bool is_term_print = false;
	bool need_print = false;
	int x_ally = -1;
	int y_ally = -1;
	int x_enemy = -1;
	int y_enemy = -1;
	std::vector<Coord> movable_grids;
	std::vector<Coord> attack_grids;
	sf::Vector2i mouse_pos;
	sf::Vector2u mouse_pos_grid;
	sf::Vector2i map_size(room.Rows(), room.Cols());

	//Text GUI
	sf::Font font;
	font.loadFromFile("../../../font/Roboto-Medium.ttf");
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	text.setPosition(grid_size * map_size.x + 20.f, 20.f);
	text.setLineSpacing(1.5f);
	text.setString("");

	sf::Text terminal;
	terminal.setFont(font);
	terminal.setCharacterSize(20);
	terminal.setFillColor(sf::Color::White);
	terminal.setPosition(20.f, grid_size * map_size.y + 20.f);
	terminal.setLineSpacing(1.5f);
	terminal.setString("");
	
	//Map GUI
	std::vector<std::vector<sf::RectangleShape>> tile_map;
	tile_map.resize(map_size.x, std::vector<sf::RectangleShape>());
	for (int x = 0; x < map_size.x; x++)
	{
		tile_map[x].resize(map_size.y, sf::RectangleShape());
		for (int y = 0; y < map_size.y; y++)
		{
			tile_map[x][y].setSize(sf::Vector2f(grid_size, grid_size));
			if (map[y][x] < 0) tile_map[x][y].setFillColor(red);
			else if (map[y][x] == 0) tile_map[x][y].setFillColor(green);
			else if (inRange(map[y][x], 0, 6)) tile_map[x][y].setFillColor(blue);
			else if (map[y][x] == 6)
			{
				tile_map[x][y].setFillColor(sf::Color::White);
				tile_map[x][y].setTexture(&rock);
			}
			else if (map[y][x] == 7)
			{
				tile_map[x][y].setFillColor(sf::Color::White);
				tile_map[x][y].setTexture(&treasure_close);
			}
			else if (map[y][x] == 8)
			{
				tile_map[x][y].setFillColor(sf::Color::White);
				tile_map[x][y].setTexture(&treasure_open);
			}
			tile_map[x][y].setOutlineThickness(1.f);
			tile_map[x][y].setOutlineColor(sf::Color::Black);
			tile_map[x][y].setPosition(x * grid_size, y * grid_size);
		}
	}

	//Create the selector
	sf::RectangleShape tile_mouse(sf::Vector2f(grid_size, grid_size));
	tile_mouse.setFillColor(sf::Color::Transparent);
	tile_mouse.setOutlineThickness(1.5f);
	tile_mouse.setOutlineColor(sf::Color::Yellow);
	
	//Create the window
	sf::RenderWindow window(sf::VideoMode(1620, 960), "Dungeons!", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(500);

	for (int x = 0; x < map_size.y; x++)
	{
		for (int y = 0; y < map_size.x; y++) std::cout << map[x][y] << " ";
		std::cout << std::endl;
	}
	

	//////////////////////////////////////////////// RUNNING //////////////////////////////////////////////////////	

	while (window.isOpen())
	{
		//Update mouse positions
		mouse_pos = sf::Mouse::getPosition(window);
		mouse_pos_grid.x = mouse_pos.x / static_cast<unsigned>(grid_size);
		mouse_pos_grid.y = mouse_pos.y / static_cast<unsigned>(grid_size);

		//Update the selector
		tile_mouse.setPosition(mouse_pos_grid.x * grid_size, mouse_pos_grid.y * grid_size);

		//Text GUI
		std::stringstream ss;
		std::stringstream ss_term;
		if (inRange(mouse_pos_grid.x, -1, map_size.x) && inRange(mouse_pos_grid.y, -1, map_size.y))
			ss << "Grid: " << mouse_pos_grid.y << " " << mouse_pos_grid.x << "\n\n";

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
					if (evnt.key.code == sf::Keyboard::Escape) window.close();
					break;

				case sf::Event::MouseButtonPressed:
					if (evnt.key.code == sf::Mouse::Left)
						//If the click is in the grid
						if (inRange(mouse_pos_grid.x, -1, map_size.x) && inRange(mouse_pos_grid.y, -1, map_size.y)
							&& inRange(map[mouse_pos_grid.y][mouse_pos_grid.x], 0, 6) && !is_term_print)
						{
							//Remeber the click
							x_ally = mouse_pos_grid.x;
							y_ally = mouse_pos_grid.y;
							is_chosen = true;

							//Add the range
							movable_grids = room.BFS(Coord(x_ally, y_ally), allies[map[y_ally][x_ally] - 1]->GetMoveRange());
							attack_grids = room.BFS_Attack(Coord(x_ally, y_ally), allies[map[y_ally][x_ally] - 1]->GetAttackRange());
							for (Coord i : movable_grids) tile_map[i.x()][i.y()].setFillColor(blue_light);
							for (Coord i : attack_grids)
							{
								tile_map[i.x()][i.y()].setFillColor(sf::Color::White);
								tile_map[i.x()][i.y()].setTexture(&attackable);
							}
						}
					break;

				case sf::Event::MouseButtonReleased:
					if (evnt.key.code == sf::Mouse::Left && is_chosen && !is_term_print)
						if (x_ally != -1 && y_ally != -1)
						{
							for (Coord i : movable_grids) tile_map[i.x()][i.y()].setFillColor(green);
							for (Coord i : attack_grids) 
							{
								tile_map[i.x()][i.y()].setFillColor(red);
								tile_map[i.x()][i.y()].setTexture(NULL);
							}
							
							if (inRange(mouse_pos_grid.x, -1, map_size.x) && inRange(mouse_pos_grid.y, -1, map_size.y))
							{
								if (std::find(movable_grids.begin(), movable_grids.end(), Coord(int(mouse_pos_grid.x), int(mouse_pos_grid.y))) != movable_grids.end())
								{
									ss_term << player.Move(allies[map[y_ally][x_ally] - 1], Coord(mouse_pos_grid.x, mouse_pos_grid.y)) << std::endl;
									std::cout << ss_term.str() << std::endl;
									need_print = true;
									map = room.ToInt();
									for (int x = 0; x < map_size.x; x++)
									{
										for (int y = 0; y < map_size.y; y++)
										{
											if (map[y][x] < 0) tile_map[x][y].setFillColor(red);
											else if (map[y][x] == 0) tile_map[x][y].setFillColor(green);
											else if (inRange(map[y][x], 0, 6)) tile_map[x][y].setFillColor(blue);
											else if (map[y][x] == 6)
											{
												tile_map[x][y].setFillColor(sf::Color::White);
												tile_map[x][y].setTexture(&rock);
											}
											else if (map[y][x] == 7)
											{
												tile_map[x][y].setFillColor(sf::Color::White);
												tile_map[x][y].setTexture(&treasure_close);
											}
											else if (map[y][x] == 8)
											{
												tile_map[x][y].setFillColor(sf::Color::White);
												tile_map[x][y].setTexture(&treasure_open);
											}
											tile_map[x][y].setOutlineThickness(1.f);
											tile_map[x][y].setOutlineColor(sf::Color::Black);
											tile_map[x][y].setPosition(x * grid_size, y * grid_size);
										}
									}

									//tile_map[x_ally][y_ally].setFillColor(green);
									//tile_map[mouse_pos_grid.x][mouse_pos_grid.y].setFillColor(blue);
									//map[mouse_pos_grid.y][mouse_pos_grid.x] = map[y_ally][x_ally];
									//map[y_ally][x_ally] = 0;
								}
								//else if (std::find(attack_grids.begin(), attack_grids.end(), Coord(int(mouse_pos_grid.x), int(mouse_pos_grid.y))) != attack_grids.end()
								else if (map[mouse_pos_grid.y][mouse_pos_grid.x] < 0)
								{
									std::cout << ss_term.str().length() << std::endl;
									ss_term << player.Attack(allies[map[y_ally][x_ally] - 1], enemies[abs(map[mouse_pos_grid.y][mouse_pos_grid.x]) - 1]) << std::endl;
									std::cout << ss_term.str().length() << std::endl;
									need_print = true;
								}
								else if (mouse_pos_grid.x != x_ally || mouse_pos_grid.y != y_ally)
								{
									//temp = tile_map[mouse_pos_grid.x][mouse_pos_grid.y].getFillColor();
									//tile_map[mouse_pos_grid.x][mouse_pos_grid.y].setFillColor(sf::Color::Black);
									ss_term << "Unit cannot move there!\n\n";
									need_print = true;
								}
							}
							
							is_chosen = false;
							x_ally = -1;
							y_ally = -1;
						}

				default:
					break;
			}
		}

		//Handle mouse in the grid or not
		if (inRange(mouse_pos_grid.x, -1, map_size.x) && inRange(mouse_pos_grid.y, -1, map_size.y))
		{
			if (is_chosen) tile_mouse.setFillColor(yellow);
			else tile_mouse.setFillColor(sf::Color::Transparent);
			tile_mouse.setOutlineColor(sf::Color::Yellow);
		}
		else 
		{
			tile_mouse.setFillColor(sf::Color::Transparent);
			tile_mouse.setOutlineColor(sf::Color::Transparent);
		}

		/*
		//Handle if mouse points to enemies
		if (inRange(mouse_pos_grid.x, -1, map_size.x) && inRange(mouse_pos_grid.y, -1, map_size.y) && !is_chosen)
		{
			if (map[mouse_pos_grid.y][mouse_pos_grid.x] < 0)
			{
				if (x_enemy != mouse_pos_grid.x || y_enemy != mouse_pos_grid.y)
				{
					for (Coord i : movable_grids)
						if (map[i.y()][i.x()] == 0) tile_map[i.x()][i.y()].setFillColor(green);
				}
				else
				{
					movable_grids = room.BFS(Coord(mouse_pos_grid.x, mouse_pos_grid.y), enemies[abs(map[mouse_pos_grid.y][mouse_pos_grid.x]) - 1]->GetMoveRange());
					for (Coord i : movable_grids)
                		if (map[i.y()][i.x()] == 0) tile_map[i.x()][i.y()].setFillColor(red_light_2);
				}
				
				x_enemy = mouse_pos_grid.x;
				y_enemy = mouse_pos_grid.y;
			}
			else
			{
				for (Coord i : movable_grids)
					if (map[i.y()][i.x()] == 0) tile_map[i.x()][i.y()].setFillColor(green);
				x_enemy = -1;
				y_enemy = -1;
			}
		}*/

		//Handle clicks to an immovable cell | Temporary change color of the cell
		/*
		if (inRange(mouse_pos_grid.x, -1, map_size.x) && inRange(mouse_pos_grid.y, -1, map_size.y) && is_wrong_click)
		{
			sf::sleep(sf::seconds(0.5f));
			tile_map[mouse_pos_grid.x][mouse_pos_grid.y].setFillColor(temp);
			is_wrong_click = false;
		}
		if (inRange(mouse_pos_grid.x, -1, map_size.x) && inRange(mouse_pos_grid.y, -1, map_size.y)
		    && tile_map[mouse_pos_grid.x][mouse_pos_grid.y].getFillColor() == sf::Color::Black) is_wrong_click = true;*/
		if (is_term_print && !need_print)
		{
			sf::sleep(sf::seconds(0.3f));
			is_term_print = false;
		}
		if (ss_term.str().length() > 0 && need_print)
		{
			is_term_print = true;
			need_print = false;
		}

		//Text GUI
		if (inRange(mouse_pos_grid.x, -1, map_size.x) && inRange(mouse_pos_grid.y, -1, map_size.y))
		{
			if (is_chosen) ss << allies[map[y_ally][x_ally] - 1]->Description() << std::endl << std::endl;
			
			if (tile_map[mouse_pos_grid.x][mouse_pos_grid.y].getFillColor() != sf::Color::Black)
			{
				if (inRange(map[mouse_pos_grid.y][mouse_pos_grid.x], 0, 6) && (x_ally != mouse_pos_grid.x || y_ally != mouse_pos_grid.y))
					ss << allies[map[mouse_pos_grid.y][mouse_pos_grid.x] - 1]->Description();
				else if (map[mouse_pos_grid.y][mouse_pos_grid.x] < 0)
					ss << enemies[abs(map[mouse_pos_grid.y][mouse_pos_grid.x]) - 1]->Description();
				else if (map[mouse_pos_grid.y][mouse_pos_grid.x] == 7)
					ss << "TREASURE!\n";
				else if (map[mouse_pos_grid.y][mouse_pos_grid.x] == 8)
					ss << "TREASURE OPENED\n";
			}
		}
		text.setString(ss.str());
		terminal.setString(ss_term.str());

		///////////////// Clear and draw /////////////////
		window.clear();

		for (int x = 0; x < map_size.x; x++)
			for (int y = 0; y < map_size.y; y++) window.draw(tile_map[x][y]);
		window.draw(tile_mouse);
		window.draw(text);
		window.draw(terminal);

		window.display();
	}

	return 0;
}