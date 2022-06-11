#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<vector>
#include<ctime>
#include<iostream>

class Bot
{
private:
	//Variables
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Objects
	sf::RectangleShape board;
	sf::RectangleShape reset;
	sf::RectangleShape result;
	std::vector<sf::RectangleShape> box;

	//Textures
	sf::Texture boardTexture;
	sf::Texture resetTexture;
	sf::Texture resultTexture;
	sf::Texture def;
	sf::Texture circle;
	sf::Texture cross;

	//Mouse position
	sf::Vector2f mousePosition;

	//Logic
	bool clickedBox[9];
	std::vector<bool>circleWin;
	std::vector<bool>crossWin;
	bool player = true;
	bool isWin = false;

	//Bot
	int playerLastMove;
	int botMove = 1;
	bool playerS = true;
	bool botMoved = false;

	//Private functions
	void initWindow();
	void initBoard();
	void initBoxes();
	void drawBoxes();

	//Bot functions
	void checkBox(int a);
	void botStart();
	void winCheck(std::vector<bool> tab);
	void playerStart();
	void botLogic();

public:
	Bot();
	~Bot();

	const bool running() const;
	void poolEvent();
	void updateMousePosition();
	void updateBoxes();
	void resetGame();
	void gameLogic();
	void update();
	void render();
};