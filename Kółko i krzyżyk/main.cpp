#include "Game.h"
#include "Bot.h"
#include<Windows.h>

int main()
{
	::ShowWindow(GetConsoleWindow(), SW_HIDE);
	sf::RenderWindow window(sf::VideoMode(500, 500), "Menu", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);
	sf::Event ev;
	sf::Vector2f mousePosition;

	sf::RectangleShape header;
	sf::Texture headerTexture;
	headerTexture.loadFromFile("Textures/header.png");
	header.setPosition(50.f, 50.f);
	header.setSize(sf::Vector2f(400.f, 100.f));
	header.setFillColor(sf::Color::Green);
	header.setTexture(&headerTexture);

	sf::RectangleShape single;
	sf::Texture singleTexture;
	singleTexture.loadFromFile("Textures/single.png");
	single.setPosition(50.f, 200.f);
	single.setSize(sf::Vector2f(400.f, 100.f));
	single.setTexture(&singleTexture);
	
	

	sf::RectangleShape bot;
	sf::Texture botTexture;
	botTexture.loadFromFile("Textures/bot.png");
	bot.setPosition(50.f, 350.f);
	bot.setSize(sf::Vector2f(400.f, 100.f));
	bot.setTexture(&botTexture);
	

    while (window.isOpen())
    {
		mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (ev.key.code == sf::Keyboard::Escape)
					window.close();
				break;
			}
		}
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (single.getGlobalBounds().contains(mousePosition))
			{
				Game game;
				while (game.running())
				{
					game.update();
					game.render();
				}
			}
			else if (bot.getGlobalBounds().contains(mousePosition))
			{
				Bot bot;
				while (bot.running())
				{
					bot.update();
					bot.render();
				}
			}			
		}

		window.clear();
		window.draw(header);
		window.draw(single);
		window.draw(bot);
		window.display();
    }
	
    return 0;
}