#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "Room.hpp"
#include "Square.hpp"
#include "Item.hpp"

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Network.hpp>
#include <SFML\Audio.hpp>

using namespace std;
int main()
{
   // Create the window
   sf::RenderWindow window(sf::VideoMode(1200, 720), "Dungeons!", sf::Style::Titlebar | sf::Style::Close);
   window.setFramerateLimit(500);

   // ##############################################
   // State 1: Start Screen
   // ##############################################
   sf::Font font;
   if (!font.loadFromFile("../../../font/arial.ttf"))
   {
   }
   sf::Text text;
   text.setFont(font);
   text.setCharacterSize(40);
   text.setFillColor(sf::Color::Red);
   text.setStyle(sf::Text::Bold);
   text.setPosition(600, 360);
   text.setString("Dungeon\nPress Enter to start\nPress 'M' to enter menu");
   window.clear();
   window.draw(text);

   window.display();
   while (true)
   {
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
         break;
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
         break;
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
      {
         cout << "Called menu" << endl;
         // TODO: Implement Menu
         break;
      }
   }
   // ####################END OF STATE 1##########################

   // ##############################################
   // State 2: Dungeon/Room
   // ##############################################

   string state_type = "dungeon";
   string state_number = "0";
   vector<Enemy *> e;
   vector<Ally *> a;
   vector<Item> *i = new vector<Item>{};
   //Battlefield temp(20, 12, e, a, i);
   // FIXME: Error occurred here: LNK2019: unresolved external symbol
   /*Determine the type of square block*/
   // string determineType(Square s)
   // {
   //    Wall *w = dynamic_cast<Wall *>(s);
   //    Floor *f = dynamic_cast<Floor *>(s);
   //    Treasure *t = dynamic_cast<Treasure *>(s);
   //    if (w != null)
   //    {
   //       return "Wall";
   //    }
   //    else if (f != null)
   //    {
   //       return "Floor";
   //    }
   //    else
   //    {
   //       return "Treasure";
   //    }
   // }
   // vector<string> design{".....###..1.###.....",
   //  "...###........###...",
   //  "...#.####...#...#...",
   //  "##.....##...##....##",
   //  "##..........########",
   //  "##....##....##....##",
   //  "##....##....###..###",
   //  "##....##..........##",
   //  "########....########",
   //  "......##....##......",
   //  "............##....##",
   //  "......##..........##"};

   // string status = temp.FromString(design);

   // Some conditions to determine the correct room (=Battlefiled)
   // Set variables
   float grid_size = 60.0;
   sf::Vector2i mouse_pos_window;
   sf::Vector2u mouse_pos_grid;
   bool isClick = false;

   //Create the map
   vector<vector<sf::RectangleShape>> tile_map;
   sf::Vector2i map_size(20, 12);
   // FIXME: Cannot resize
   tile_map.resize(map_size.x, vector<sf::RectangleShape>());

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
      if (state_type == "dungeon")
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
               if (evnt.key.code == sf::Keyboard::Escape)
                  window.close();
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
            tile_mouse.setFillColor(sf::Color::Blue);
            isClick = true;
         }
         else
         {
            if (isClick)
            {
               isClick = false;
               tile_mouse.setFillColor(sf::Color::Transparent);
               if (tile_map[mouse_pos_grid.x][mouse_pos_grid.y].getFillColor() == sf::Color::Cyan)
                  tile_map[mouse_pos_grid.x][mouse_pos_grid.y].setFillColor(sf::Color::Red);
               else
                  tile_map[mouse_pos_grid.x][mouse_pos_grid.y].setFillColor(sf::Color::Cyan);
            }
         }

         //Clear and draw
         window.clear();

         for (int x = 0; x < map_size.x; x++)
            for (int y = 0; y < map_size.y; y++)
               window.draw(tile_map[x][y]);
         window.draw(tile_mouse);

         window.display();
      }
      else
      {
         // Another scene
      }
   }

   return 0;
}