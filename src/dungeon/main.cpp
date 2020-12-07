/**
#include<iostream>
#include<sstream>
#include<vector>

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Network.hpp>
#include <SFML\Audio.hpp>

int main()
{
	//Create the window
	sf::RenderWindow window(sf::VideoMode(1200, 720), "Dungeons!", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(500);

	//Set variables
	float grid_size = 60.f;
	sf::Vector2i mouse_pos_window;
	sf::Vector2u mouse_pos_grid;
	bool isClick = false;

	//Create the map
	std::vector<std::vector<sf::RectangleShape>> tile_map;
	sf::Vector2i map_size(20, 12);
	tile_map.resize(map_size.x, std::vector<sf::RectangleShape>());

	for (int x = 0; x < map_size.x; x++)
	{
		tile_map[x].resize(map_size.y, sf::RectangleShape());
		for (int y = 0; y < map_size.y; y++)
		{
			tile_map[x][y].setSize(sf::Vector2f(grid_size, grid_size));
			tile_map[x][y].setFillColor(sf::Color::Cyan);
			tile_map[x][y].setOutlineThickness(1.f);
			tile_map[x][y].setOutlineColor(sf::Color::Black);
			tile_map[x][y].setPosition(x * grid_size, y * grid_size);
		}
	}

	//Create the selector
	sf::RectangleShape tile_mouse(sf::Vector2f(grid_size, grid_size));
	tile_mouse.setFillColor(sf::Color::Transparent);
	tile_mouse.setOutlineThickness(1.f);
	tile_mouse.setOutlineColor(sf::Color::Red);

	while (window.isOpen())
	{
		//Update mouse positions
		mouse_pos_window = sf::Mouse::getPosition(window);
		mouse_pos_grid.x = mouse_pos_window.x / static_cast<unsigned>(grid_size);
		mouse_pos_grid.y = mouse_pos_window.y / static_cast<unsigned>(grid_size);

		//Update the selector
		tile_mouse.setPosition(mouse_pos_grid.x * grid_size, mouse_pos_grid.y * grid_size);

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

				default:
					break;
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			mouse_pos_window = sf::Mouse::getPosition(window);
			mouse_pos_grid.x = mouse_pos_window.x / static_cast<unsigned>(grid_size);
			mouse_pos_grid.y = mouse_pos_window.y / static_cast<unsigned>(grid_size);
			tile_mouse.setFillColor(sf::Color::Red);
			isClick = true;
		}
		else
		{
			if (isClick)
			{
				isClick = false;
				tile_mouse.setFillColor(sf::Color::Transparent);
				if (tile_map[mouse_pos_grid.x][mouse_pos_grid.y].getFillColor() == sf::Color::Cyan) tile_map[mouse_pos_grid.x][mouse_pos_grid.y].setFillColor(sf::Color::Red);
				else tile_map[mouse_pos_grid.x][mouse_pos_grid.y].setFillColor(sf::Color::Cyan);
			}
		}

		//Clear and draw
		window.clear();

		for (int x = 0; x < map_size.x; x++)
			for (int y = 0; y < map_size.y; y++) window.draw(tile_map[x][y]);
		window.draw(tile_mouse);

		window.display();
	}

	return 0;
} */