#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cmath>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include "Player.cpp"
#include "Item.hpp"
#include "Grid.cpp"
#define START_SCREEN_STAGE 0
#define STORY_STAGE 1
#define STORE_FUNCTIONALITY_SELECTION_STAGE 2
#define STORE_TRADE_STAGE 3
#define BATTLE_ROOM_STAGE 4

using namespace std;

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

int main()
{

    string projectPath = filesystem::current_path().generic_string();
    projectPath = projectPath.substr(0, projectPath.find("dungeon-2020-4") + 14);
    string resourcePath = projectPath + "/resource";
    cout << projectPath << endl;
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

    unsigned int windowX = 1200;
    unsigned int windowY = 720;
    unsigned int buttonX = 400;
    unsigned int buttonY = 200;

    //Create the window
    sf::RenderWindow window(sf::VideoMode((int)windowX, (int)windowY), "Dungeons!", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(500);
    float grid_size = 60.f;
    bool direction = true;
    int text_shine = 0;
    // Initial stage of the program
    int stage = START_SCREEN_STAGE;
    ifstream ifs(resourcePath + "/story.txt");
    string story((istreambuf_iterator<char>(ifs)),
                 (istreambuf_iterator<char>()));
    string selectedCase = "Buy";

    sf::Font font;
    font.loadFromFile(resourcePath + "/Roboto-Medium.ttf");
    sf::Vector2i mouse_pos;
    sf::Event event;

    while (window.isOpen())
    {
        window.clear();
        textureCollection.clear();
        if (stage == STORE_FUNCTIONALITY_SELECTION_STAGE)
        {
            int opacity = (int)(50 * sin(text_shine / 20.0f) + 205);
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

            sf::Text title;
            title.setFont(font);
            title.setFillColor(sf::Color::White);
            title.setStyle(sf::Text::Bold);
            title.setString("Name       Description                              Price           Quantity     Action");
            title.setPosition(80, 150);
            window.draw(title);
            float text_location_y = 210;
            vector<sf::RectangleShape> actionButtons;
            for (auto itemset : player.GetInventory())
            {
                sf::Text name, description, price, quantity;

                name.setFont(font);
                name.setFillColor(sf::Color::White);
                name.setString(itemset.first.GetName());
                name.setPosition(80, text_location_y);

                description.setFont(font);
                description.setFillColor(sf::Color::White);
                description.setString(itemset.first.GetDescription());
                description.setPosition(220, text_location_y);

                price.setFont(font);
                price.setFillColor(sf::Color::White);
                price.setString(to_string(itemset.first.GetPrice()));
                price.setPosition(620, text_location_y);

                quantity.setFont(font);
                quantity.setFillColor(sf::Color::White);
                quantity.setString(to_string(itemset.second));
                quantity.setPosition(780, text_location_y);

                sf::RectangleShape actionButtonRect = createButton(940, text_location_y, 190, 60, resourcePath + "/" + selectedCase + ".png");

                window.draw(name);
                window.draw(description);
                window.draw(price);
                window.draw(quantity);
                window.draw(actionButtonRect);

                text_location_y += 60;
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
                        for (auto b : actionButtons)
                            if (buttonClicked(b, mouse_pos))
                            {
                                int itemNum = (int)(b.getPosition().y - 210) / 60;
                                // FIXME: Do correct operation accordingly
                            }
                }
        }
        else if (stage == BATTLE_ROOM_STAGE)
        {
        }
        else if (stage == START_SCREEN_STAGE)
        {
            sf::Text dungeonTitle, clickToStart;

            dungeonTitle.setFont(font);
            dungeonTitle.setFillColor(sf::Color::White);
            dungeonTitle.setString("Dungeon Crawler!!!");
            dungeonTitle.setCharacterSize(72);
            dungeonTitle.setStyle(sf::Text::Bold);

            sf::FloatRect titleRect = dungeonTitle.getLocalBounds();
            dungeonTitle.setOrigin(titleRect.left + titleRect.width / 2.0f,
                                   titleRect.top + titleRect.height / 2.0f);
            dungeonTitle.setPosition(windowX / 2.0f, windowY * 0.2f);

            clickToStart.setFont(font);
            clickToStart.setFillColor(sf::Color::White);
            clickToStart.setString("Click anywhere to start");
            sf::FloatRect ctsRect = clickToStart.getLocalBounds();
            clickToStart.setOrigin(ctsRect.left + ctsRect.width / 2.0f,
                                   ctsRect.top + ctsRect.height / 2.0f);
            clickToStart.setPosition(windowX / 2.0f, windowY * 0.8f);

            window.draw(dungeonTitle);
            if (text_shine % 800 > 400)
                window.draw(clickToStart);

            if (window.pollEvent(event))
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::MouseButtonReleased)
                {
                    text_shine = 0;
                    stage = STORY_STAGE;
                }
        }
        else if (stage == STORY_STAGE)
        {
            sf::Text storyText;
            storyText.setFont(font);
            storyText.setFillColor(sf::Color::White);
            storyText.setString(story.substr(0, text_shine / 6));

            sf::FloatRect storyRect = storyText.getLocalBounds();
            storyText.setOrigin(storyRect.left + storyRect.width / 2.0f,
                                storyRect.top);
            storyText.setPosition(windowX / 2.0f, windowY * 0.1f);
            window.draw(storyText);
            if (size(story) == size(storyText.getString().toAnsiString()))
                stage = STORE_FUNCTIONALITY_SELECTION_STAGE; // Here should be something else
            if (window.pollEvent(event) && event.type == sf::Event::Closed)
                window.close();
        }
        else
            window.close();

        window.display();
        text_shine++;
    }

    return 0;
}