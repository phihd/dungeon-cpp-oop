#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Network.hpp>
#include <SFML\Audio.hpp>
#include "Player.cpp"
#include "Item.hpp"
//#include "Stat.hpp"
//#include "Room.hpp"
// #include "Unit.hpp"
// #include "World.hpp"
#include "Grid.cpp"
// #include "Coord.hpp"
// #include "Square.hpp"

using namespace std;
int main()
{   
    
    Player player = Player("Player 1");
    Stat universalStatus = Stat(1, 1, 1, 1, 1, 1, 1);
    player.AddItem(Item("a", "a", universalStatus, 5), 12);
    player.AddItem(Item("bdscds", "a", universalStatus, 3), 1);
    player.AddItem(Item("c", "a", universalStatus, 1), 123);
    player.AddItem(Item("dcsd", "a", universalStatus, 7), 1);
    player.AddItem(Item("e", "a", universalStatus, 100), 5);
    player.AddItem(Item("f", "a", universalStatus, 2), 10);
    player.AddItem(Item("g", "a", universalStatus, 2), 1200);
    player.AddItem(Item("h", "a", universalStatus, 2), 2);

    unsigned int window_x = 1200;
    unsigned int window_y = 720;
    unsigned int button_x = 400;
    unsigned int button_y = 200;
    //Create the window
    sf::RenderWindow window(sf::VideoMode(window_x, window_y), "Dungeons!", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(500);
    float grid_size = 60.f;

    sf::Vector2i mouse_pos_window;
    sf::Vector2u mouse_pos_grid;
    bool isClick = false;
    bool WINDOW_HAS_FOCUS = false;
    //Create the map
    std::vector<std::vector<sf::RectangleShape>> tile_map;
    sf::Vector2i map_size(20, 12);
    bool IS_MAIN_MENU_INTERFACE = false;
    // bool display_animation = true;
    bool direction = true;
    int transparency = 155;
    string selected_case = "Buy";

    while (window.isOpen())
    {
        //Update mouse positions
        // mouse_pos_window = sf::Mouse::getPosition(window);
        // mouse_pos_grid.x = mouse_pos_window.x / static_cast<unsigned>(grid_size);
        // mouse_pos_grid.y = mouse_pos_window.y / static_cast<unsigned>(grid_size);

        // //Update the selector
        // tile_mouse.setPosition(mouse_pos_grid.x * grid_size, mouse_pos_grid.y * grid_size);
        window.clear();
        sf::Font font;
        font.loadFromFile("../../font/Roboto-Medium.ttf");
        if (isClick /*IS_MAIN_MENU_INTERFACE*/)
        {
            // display_animation = true;
            sf::Vector2f buyLoc(window_x * 0.25 - button_x / 2, window_y * 0.25 - button_y / 2);
            sf::Vector2f sellLoc(window_x * 0.75 - button_x / 2, window_y * 0.25 - button_y / 2);
            sf::Vector2f upgradeLoc(window_x * 0.25 - button_x / 2, window_y * 0.75 - button_y / 2);
            sf::Vector2f quitLoc(window_x * 0.75 - button_x / 2, window_y * 0.75 - button_y / 2);
            sf::Vector2f buttonSize(button_x, button_y);
            sf::Texture t;
            t.loadFromFile("../../font/button.png");
            sf::RectangleShape buyButton(buttonSize);
            buyButton.setTexture(&t);
            buyButton.setPosition(buyLoc);
            buyButton.setFillColor(sf::Color::Color(255, 255, 255, transparency));
            sf::RectangleShape sellButton(buttonSize);
            sellButton.setTexture(&t);
            sellButton.setPosition(sellLoc);
            sellButton.setFillColor(sf::Color::Color(255, 255, 255, transparency));
            sf::RectangleShape upgradeButton(buttonSize);
            upgradeButton.setTexture(&t);
            upgradeButton.setPosition(upgradeLoc);
            upgradeButton.setFillColor(sf::Color::Color(255, 255, 255, transparency));
            sf::RectangleShape quitButton(buttonSize);
            quitButton.setTexture(&t);
            quitButton.setPosition(quitLoc);
            quitButton.setFillColor(sf::Color::Color(255, 255, 255, transparency));
            window.draw(buyButton);
            window.draw(sellButton);
            window.draw(upgradeButton);
            window.draw(quitButton);
            if (direction)
            {
                if (++transparency == 255)
                    direction ^= true;
            }
            else
            {
                if (--transparency == 155)
                    direction ^= true;
            }
        }
        else
        {

            sf::Vector2f backButtonPos(50, 30);
            sf::Vector2f backButtonSize(200, 100);
            sf::Texture backButton;

            backButton.loadFromFile("../../font/stone_arrow.png");
            sf::RectangleShape backButtonRect(backButtonSize);
            backButtonRect.setTexture(&backButton);
            backButtonRect.setPosition(backButtonPos);
            // if (display_animation-- > 0)  back_buttonRect.setOutlineColor(sf::Color::Blue);
            window.draw(backButtonRect);
            sf::Text title;
            sf::Vector2f titlePos(80, 150);
            title.setFont(font);
            title.setFillColor(sf::Color::White);
            title.setStyle(sf::Text::Bold);
            title.setString("Name       Description                              Price           Quantity     Action");
            title.setPosition(titlePos);
            window.draw(title);
            unsigned int text_location_y = 210;
            for (auto itemset : player.GetInventory())
            {
                sf::Text name, description, price, quantity;
                sf::Vector2f namePos(80, text_location_y);
                sf::Vector2f descriptionPos(220, text_location_y);
                sf::Vector2f pricePos(620, text_location_y);
                sf::Vector2f quantityPos(780, text_location_y);
                sf::Vector2f actionButtonPos(940, text_location_y - 12);
                name.setFont(font);
                name.setFillColor(sf::Color::White);
                name.setString(itemset.first.GetName());
                name.setPosition(namePos);

                description.setFont(font);
                description.setFillColor(sf::Color::White);
                description.setString(itemset.first.GetDescription());
                description.setPosition(descriptionPos);

                price.setFont(font);
                price.setFillColor(sf::Color::White);
                price.setString(to_string(itemset.first.GetPrice()));
                price.setPosition(pricePos);

                quantity.setFont(font);
                quantity.setFillColor(sf::Color::White);
                quantity.setString(to_string(itemset.second));
                quantity.setPosition(quantityPos);

                window.draw(name);
                window.draw(description);
                window.draw(price);
                window.draw(quantity);
                sf::Texture actionButton;
                actionButton.loadFromFile("../../font/" + selected_case + ".png");
                sf::Vector2f actionButtonSize(190, 60);
                sf::RectangleShape actionButtonRect(actionButtonSize);
                actionButtonRect.setTexture(&actionButton);
                actionButtonRect.setPosition(actionButtonPos);
                window.draw(actionButtonRect);

                text_location_y += 60;
            }
            // display_animation = false;
        }

        //Events
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {

            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

                // case sf::Event::MouseEntered:
                //     WINDOW_HAS_FOCUS = true;

                // case sf::Event::MouseLeft:
                //     WINDOW_HAS_FOCUS = false;

            case sf::Event::KeyPressed:
                if (evnt.key.code == sf::Keyboard::Escape)
                    window.close();
                break;
            case sf::Event::MouseButtonReleased:
                isClick = !isClick;
                break;

            default:
                break;
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {

            mouse_pos_window = sf::Mouse::getPosition(window);
            // mouse_pos_grid.x = mouse_pos_window.x;
            // mouse_pos_grid.y = mouse_pos_window.y;
            // cout << mouse_pos_grid.x << endl;
            // cout << mouse_pos_grid.y << endl;
        }
        // if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        // {
        // 	mouse_pos_window = sf::Mouse::getPosition(window);
        // 	mouse_pos_grid.x = mouse_pos_window.x / static_cast<unsigned>(grid_size);
        // 	mouse_pos_grid.y = mouse_pos_window.y / static_cast<unsigned>(grid_size);
        // 	tile_mouse.setFillColor(sf::Color::Red);
        // 	isClick = true;
        // }
        // else
        // {
        // 	if (isClick)
        // 	{
        // 		isClick = false;
        // 		tile_mouse.setFillColor(sf::Color::Transparent);
        // 		if (tile_map[mouse_pos_grid.x][mouse_pos_grid.y].getFillColor() == sf::Color::Cyan) tile_map[mouse_pos_grid.x][mouse_pos_grid.y].setFillColor(sf::Color::Red);
        // 		else tile_map[mouse_pos_grid.x][mouse_pos_grid.y].setFillColor(sf::Color::Cyan);
        // 	}
        // }

        //Clear and draw

        // for (int x = 0; x < map_size.x; x++)
        // 	for (int y = 0; y < map_size.y; y++) window.draw(tile_map[x][y]);
        // window.draw(tile_mouse);

        window.display();
    }

    return 0;
}