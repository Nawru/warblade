#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <sstream>
#include <string>

#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Gui.h"

using namespace sf;
using namespace std;


Gui::Gui()
{



	if (!font.loadFromFile("Fonts\\No Virus.ttf"))
	{
		cout << "FAILED GUI FONTS LOAD!" << endl;
	}

	// HP BAR
	this->backHPbar.setSize(Vector2f(280, 20));
	this->backHPbar.setPosition(10, 690);
	this->backHPbar.setFillColor(Color::Color(105, 105, 105, 255));

	this->HPbar.setSize(Vector2f(280, 20));
	this->HPbar.setPosition(10, 690);
	this->HPbar.setFillColor(Color::Green);

	// LEVEL TEXT
	this->level.setFont(font);
	this->level.setString("lvl: 1");
	this->level.setCharacterSize(30);
	this->level.setPosition(Vector2f(380, 680));

	// POINTS TEXT
	this->points.setFont(font);
	this->points.setString("0");
	this->points.setCharacterSize(30);
	this->points.setPosition(Vector2f(600, 680));

	// GAME OVER TEXT
	this->gameOverText.setFont(font);
	this->gameOverText.setString("GAME OVER");
	this->gameOverText.setCharacterSize(100);
	this->gameOverText.setFillColor(Color::Red);
	this->gameOverText.setPosition(Vector2f(200, 200));
}

Gui::~Gui()
{
}


void Gui::setGUIhp(int hp)
{

	this->HPbar.setSize(Vector2f((this->backHPbar.getGlobalBounds().width / 100) * hp, this->backHPbar.getGlobalBounds().height));

}

void Gui::setGUIspeed(int speed)
{
}

void Gui::setGUIbullet(int bullet)
{
}

void Gui::setGUIlevel(int level)
{

	ss.str("");
	ss << "lvl: " << level;
	this->level.setString(ss.str());

}

void Gui::setGUIpoints(int points)
{

	ss.str("");
	ss << points;
	this->points.setString(ss.str());

}

void Gui::setGUImoney(int money)
{

}

void Gui::renderGameOver()
{
	if(this->gameOver == false)
		this->gameOver = true;
	else
		this->gameOver = false;
}


void Gui::reder(RenderTarget* target)
{
	if (gameOver == true)
		target->draw(this->gameOverText);
	else
	{
		target->draw(this->backHPbar);
		target->draw(this->HPbar);
		target->draw(this->level);
		target->draw(this->points);
	}
}

