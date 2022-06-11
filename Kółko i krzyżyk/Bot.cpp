#include "Bot.h"

//Private functions
void Bot::initWindow()
{
	this->videoMode.height = 710;
	this->videoMode.width = 600;
	this->window = new sf::RenderWindow(this->videoMode, "Bot i krzyzyk", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Bot::initBoard()
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

void Bot::initBoxes()
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

void Bot::drawBoxes()
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

void Bot::checkBox(int a)
{
	this->clickedBox[a] = true;
	this->box[a].setTexture(&this->cross);
	this->player = true;
	this->crossWin[a] = true;
	botMove++;
}

void Bot::winCheck(std::vector<bool> tab)
{
	bool moved = false;
	int a = 0;
	int b = 3;
	//poziomo
	for (int j = 0;j < 3;j++)
	{
		int win = 0;
		for (int i = a;i < b;i++)
		{
			if (tab[i])
				win++;
		}
		if (win == 2)
		{
			for (int i = a;i < b;i++)
			{
				if (!tab[i] && !clickedBox[i])
				{
					Bot::checkBox(i);
					win = 0;
					this->botMoved = true;
					moved = true;
					break;
				}
			}
		}
		a += 3;
		b += 3;
	}

	//pionowo
	a = 0;
	b = 7;
	if (!moved)
	{
		for (int j = 0;j < 3;j++)
		{
			int win = 0;
			for (int i = a;i < b;i += 3)
			{
				if (tab[i])
					win++;
			}
			if (win == 2)
			{
				for (int i = a;i < b;i += 3)
				{
					if (!tab[i] && !clickedBox[i])
					{
						Bot::checkBox(i);
						win = 0;
						this->botMoved = true;
						moved = true;
						break;
					}
				}
			}
			a++;
			b++;
		}
	}
	//na skos
	a = 0;
	b = 9;
	int c = 4;
	if (!moved)
	{
		for (int j = 0;j < 2;j++)
		{
			int win = 0;
			for (int i = a;i < b;i += c)
			{
				if (tab[i])
					win++;
			}
			if (win == 2)
			{
				for (int i = a;i < b;i += c)
				{
					if (!tab[i] && !clickedBox[i])
					{
						Bot::checkBox(i);
						win = 0;
						this->botMoved = true;
						break;
					}
				}
			}
			a = 2;
			b = 7;
			c = 2;
		}
	}
}

void Bot::botStart()
{
	switch (botMove) {
	case 1:
		Bot::checkBox(8);
		break;

	case 2:
		//1
		if (playerLastMove == 1 || playerLastMove == 3 || playerLastMove == 5 || playerLastMove == 7)
			Bot::checkBox(4);
		//2
		else if (playerLastMove == 0 || playerLastMove == 2)
			Bot::checkBox(6);
		//3
		else if (playerLastMove == 6)
			Bot::checkBox(2);

		//4
		else if (playerLastMove == 4)
			Bot::checkBox(0);

		break;

	case 3:
		//1
		if (crossWin[4] == true)
		{
			if (playerLastMove == 0)
			{
				if (circleWin[1] || circleWin[7])
					Bot::checkBox(2);
				else
					Bot::checkBox(6);
			}
			else
				Bot::checkBox(0);
		}
		//2
		else if (crossWin[6])
		{
			if (playerLastMove == 7)
			{
				if (circleWin[0])
					Bot::checkBox(2);
				else if (circleWin[2])
					Bot::checkBox(0);
			}
			else
				Bot::checkBox(7);
		}
		//3
		else if (crossWin[2])
		{
			if (playerLastMove == 5)
				Bot::checkBox(0);
			else
				Bot::checkBox(5);
		}
		//4
		else if (crossWin[0])
		{
			if (playerLastMove == 2)
				Bot::checkBox(6);
			else if (playerLastMove == 6)
				Bot::checkBox(2);
			else if (playerLastMove == 1)
				Bot::checkBox(7);
			else if (playerLastMove == 3)
				Bot::checkBox(5);
			else if (playerLastMove == 5)
				Bot::checkBox(3);
			else if (playerLastMove == 7)
				Bot::checkBox(1);
		}
		break;

	case 4:
		Bot::winCheck(this->crossWin);
		if (!botMoved)
			Bot::winCheck(this->circleWin);
		if (!botMoved)
		{
			for (int i = 0;i < 9;i++)
			{
				if (!this->clickedBox[i])
				{
					Bot::checkBox(i);
					break;
				}
			}
		}
		this->botMoved = false;
		break;

		break;

	case 5:
		for (int i = 0;i < 9;i++)
		{
			if (!clickedBox[i])
				Bot::checkBox(i);
		}
		break;
	}
}

void Bot::playerStart()
{
	switch (botMove)
	{
	case 1:
		//róg (1)
		if (playerLastMove == 4)
			Bot::checkBox(8);
		//œrodek (2)
		else
			Bot::checkBox(4);
		break;

	case 2:
		if (playerLastMove == 0 && circleWin[4])
			Bot::checkBox(2);
		else
		{
			Bot::winCheck(this->crossWin);
			if (!botMoved)
				Bot::winCheck(this->circleWin);
			if (!botMoved)
			{
				for (int i = 1;i < 8;i += 2)
				{
					if (!this->clickedBox[i])
					{
						Bot::checkBox(i);
						break;
					}
				}
			}
			this->botMoved = false;
		}
		break;
	case 3:
		Bot::winCheck(this->crossWin);
		if (!botMoved)
			Bot::winCheck(this->circleWin);
		if (!botMoved)
		{
			for (int i = 0;i < 9;i++)
			{
				if (!this->clickedBox[i])
				{
					Bot::checkBox(i);
					break;
				}
			}
		}
		this->botMoved = false;
		break;
	case 4:
		Bot::winCheck(this->crossWin);
		if (!botMoved)
			Bot::winCheck(this->circleWin);
		if (!botMoved)
		{
			for (int i = 0;i < 9;i++)
			{
				if (!this->clickedBox[i])
				{
					Bot::checkBox(i);
					break;
				}
			}
		}
		this->botMoved = false;
		break;
	}
}

void Bot::botLogic()
{
	if (!playerS)
		Bot::botStart();
	else
		Bot::playerStart();
}

//Public functions

Bot::Bot()
{
	this->initWindow();
	this->initBoard();
	this->initBoxes();
}

Bot::~Bot()
{
	delete this->window;
}

const bool Bot::running() const
{
	return this->window->isOpen();
}

void Bot::poolEvent()
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

void Bot::updateMousePosition()
{
	this->mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void Bot::updateBoxes()
{
	if (this->player)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			for (int i = 0;i < 9;i++)
			{
				if (this->box[i].getGlobalBounds().contains(this->mousePosition) && !clickedBox[i])
				{
					this->clickedBox[i] = true;
					this->box[i].setTexture(&this->circle);
					this->player = false;
					this->circleWin[i] = true;
					this->playerLastMove = i;
					break;
				}
			}
		}
	}
	else if (!this->player)
	{
		this->botLogic();
	}

}

void Bot::resetGame()
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

		if (playerS)
		{
			this->playerS = false;
			this->player = false;
		}
		else if (!playerS)
		{
			this->playerS = true;
			this->player = true;
		}
		this->botMove = 1;
		this->botMoved = false;
		this->resultTexture.loadFromFile("Textures/result.png");
		this->isWin = false;
	}


	if (this->ev.type == sf::Event::MouseButtonReleased)
		if (this->ev.mouseButton.button == sf::Mouse::Left)
			pressed = false;
}

void Bot::gameLogic()
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

void Bot::update()
{
	this->poolEvent();
	this->updateMousePosition();
	this->updateBoxes();
	this->resetGame();
	this->gameLogic();
}

void Bot::render()
{
	this->window->clear();
	this->window->draw(board);
	this->window->draw(reset);
	this->window->draw(result);
	this->drawBoxes();
	this->window->display();
}