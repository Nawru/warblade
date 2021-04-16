#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <string>
#include <iostream>
#include <cmath>
#include <cstdlib>

#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Gui.h"
#include "Background.h"

using namespace sf;
using namespace std;

Background::Background()
{
	if (!this->backbround1Texture.loadFromFile("Textures/backGround1texture.png"))
	{
		cout << "LOAD BACKGROUND1 TEXTURE FAILED" << endl;
		system("pause");
	}
	if (!this->backbround2Texture.loadFromFile("Textures/backGround2texture.png"))
	{
		cout << "LOAD BACKGROUND2 TEXTURE FAILED" << endl;
		system("pause");
	}

	this->background1.setTexture(this->backbround1Texture);
	this->background1.setPosition(0.f, 0.f);
	//this->background1.setScale(1.2, 1.2);
	this->background2.setTexture(this->backbround2Texture);
	this->background2.setPosition(0.f, -(this->background2.getGlobalBounds().height));
	//this->background2.setScale(1.2, 1.2);
}

Background::~Background()
{
}

void Background::updateBackground(RenderTarget* target)
{
	if (this->background1.getPosition().y == this->background2.getGlobalBounds().height)
	{
		this->background1.setPosition(0.f, -(this->background1.getGlobalBounds().height));
	}
	if (this->background2.getPosition().y == this->background1.getGlobalBounds().height)
	{
		this->background2.setPosition(0.f, -(this->background2.getGlobalBounds().height));
	}
	this->background1.move(0.f, 1.f);
	this->background2.move(0.f, 1.f);
}

void Background::renderBackground(RenderTarget* target)
{
	target->draw(this->background1);
	target->draw(this->background2);
}
