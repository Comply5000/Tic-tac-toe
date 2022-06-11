#include "Game.h"

//Private functions
void Game::initWindow()
{
	this->videoMode.height = 710;
	this->videoMode.width = 600;
	this->window = new sf::RenderWindow(this->videoMode, "Kolko i krzyzyk", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::initBoard()
{
	this->board.setPosition(0.f, 0.f);
	this->board.setSize(sf::Vector2f(600.f, 600.f));
	this->boardTexture.loadFromFile("Textures/board.png");
	this->board.setTexture(&boardTexture);

	this->reset.setPosition(10.f, 610.f);
	this->reset.setSize(sf::Vector2f(180.f, 90.f));
	this->resetTexture.loadFromFile("Textures/reset.png");
	this->reset.setTexture(&resetTexture);

	this->result.setPosition(200.f, 610.f);
	this->result.setSize(sf::Vector2f(390.f, 90.f));
	this->result.setFillColor(sf::Color::Green);
	this->resultTexture.loadFromFile("Textures/result.png");
	this->result.setTexture(&resultTexture);
}

void Game::initBoxes()
{	
	this->def.loadFromFile("Textures/black.png");
	this->box.resize(9);
	this->circleWin.resize(9);
	this->crossWin.resize(9);

	this->box[0].setPosition(5.f, 5.f);
	this->box[0].setSize(sf::Vector2f(185.f, 185.f));
	this->box[0].setTexture(&def);

	this->box[1].setPosition(208.f, 5.f);
	this->box[1].setSize(sf::Vector2f(185.f, 185.f));
	this->box[1].setTexture(&def);

	this->box[2].setPosition(410.f, 5.f);
	this->box[2].setSize(sf::Vector2f(185.f, 185.f));
	this->box[2].setTexture(&def);

	this->box[3].setPosition(5.f, 210.f);
	this->box[3].setSize(sf::Vector2f(185.f, 185.f));
	this->box[3].setTexture(&def);

	this->box[4].setPosition(208.f, 210.f);
	this->box[4].setSize(sf::Vector2f(185.f, 185.f));
	this->box[4].setTexture(&def);

	this->box[5].setPosition(410.f, 210.f);
	this->box[5].setSize(sf::Vector2f(185.f, 185.f));
	this->box[5].setTexture(&def);

	this->box[6].setPosition(5.f, 410.f);
	this->box[6].setSize(sf::Vector2f(185.f, 185.f));
	this->box[6].setTexture(&def);

	this->box[7].setPosition(208.f, 410.f);
	this->box[7].setSize(sf::Vector2f(185.f, 185.f));
	this->box[7].setTexture(&def);

	this->box[8].setPosition(410.f, 410.f);
	this->box[8].setSize(sf::Vector2f(185.f, 185.f));
	this->box[8].setTexture(&def);

	//Setting textures
	this->circle.loadFromFile("Textures/circle.png");
	this->cross.loadFromFile("Textures/cross.png");
}

void Game::drawBoxes()
{
	this->window->draw(box[0]);
	this->window->draw(box[1]);
	this->window->draw(box[2]);
	this->window->draw(box[3]);
	this->window->draw(box[4]);
	this->window->draw(box[5]);
	this->window->draw(box[6]);
	this->window->draw(box[7]);
	this->window->draw(box[8]);
}

//Functions

Game::Game()
{
	this->initWindow();
	this->initBoard();
	this->initBoxes();
}

Game::~Game()
{
	delete this->window;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::poolEvent()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::updateMousePosition()
{
	this->mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void Game::updateBoxes()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (int i = 0;i < 9;i++)
		{
			if (this->box[i].getGlobalBounds().contains(this->mousePosition) && !clickedBox[i])
			{
				this->clickedBox[i] = true;
				if (player)
				{
					this->box[i].setTexture(&this->circle);
					this->player = false;
					this->circleWin[i] = true;
					break;
				}
				else
				{
					this->box[i].setTexture(&this->cross);
					this->player = true;
					this->crossWin[i] = true;
					break;
				}
			}
		}
	}
}

void Game::resetGame()
{
	static bool pressed = false;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->reset.getGlobalBounds().contains(this->mousePosition) && !pressed)
	{
		pressed = true;
		for (int i = 0;i < 9;i++)
		{
			this->box[i].setTexture(&def);
			this->clickedBox[i] = false;
			this->circleWin[i] = false;
			this->crossWin[i] = false;
		}		
		this->resultTexture.loadFromFile("Textures/result.png");
		this->player = true;
		this->isWin = false;
	}

	if (this->ev.type == sf::Event::MouseButtonReleased)
		if (this->ev.mouseButton.button == sf::Mouse::Left)
			pressed = false;
	
}

void Game::gameLogic()
{
	if (circleWin[0] && circleWin[1] && circleWin[2]
		|| circleWin[3] && circleWin[4] && circleWin[5]
		|| circleWin[6] && circleWin[7] && circleWin[8]
		|| circleWin[0] && circleWin[3] && circleWin[6]
		|| circleWin[1] && circleWin[4] && circleWin[7]
		|| circleWin[2] && circleWin[5] && circleWin[8]
		|| circleWin[0] && circleWin[4] && circleWin[8]
		|| circleWin[2] && circleWin[4] && circleWin[6])
	{
		for (int i = 0;i < 9;i++)
			this->clickedBox[i] = true;

		this->resultTexture.loadFromFile("Textures/circlewin.png");
		this->isWin = true;
	}

	else if (crossWin[0] && crossWin[1] && crossWin[2]
		|| crossWin[3] && crossWin[4] && crossWin[5]
		|| crossWin[6] && crossWin[7] && crossWin[8]
		|| crossWin[0] && crossWin[3] && crossWin[6]
		|| crossWin[1] && crossWin[4] && crossWin[7]
		|| crossWin[2] && crossWin[5] && crossWin[8]
		|| crossWin[0] && crossWin[4] && crossWin[8]
		|| crossWin[2] && crossWin[4] && crossWin[6])
	{
		for (int i = 0;i < 9;i++)
			this->clickedBox[i] = true;

		this->resultTexture.loadFromFile("Textures/crosswin.png");
		this->isWin = true;
	}
	if (!isWin && clickedBox[0] && clickedBox[1] && clickedBox[2]
		&& clickedBox[3] && clickedBox[4] && clickedBox[5]
		&& clickedBox[6] && clickedBox[7] && clickedBox[8])
	{
		this->resultTexture.loadFromFile("Textures/draw.png");		
	}
}

void Game::update()
{
	this->poolEvent();
	this->updateMousePosition();
	this->updateBoxes();
	this->resetGame();
	this->gameLogic();
}

void Game::render()
{
	this->window->clear();
	this->window->draw(board);
	this->window->draw(reset);
	this->window->draw(result);
	this->drawBoxes();
	this->window->display();
}
