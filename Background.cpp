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
	if (!this->backbroundTexture.loadFromFile("Textures/backgroundTexture.png"))
	{
		cout << "LOAD PLAYER TEXTURE FAILED" << endl;
		system("pause");
	}

	this->background1.setTexture(this->backbroundTexture);
	this->background1.setPosition(0.f, 0.f);
	this->background2.setTexture(this->backbroundTexture);
	this->background2.setPosition(0.f, -(this->background2.getGlobalBounds().height));
}

Background::~Background()
{
}

void Background::updateBackground(RenderTarget* target)
{
	if (this->background1.getPosition().y == target->getSize().y)
	{
		this->background1.setPosition(0.f, -(this->background1.getGlobalBounds().height));
	}
	if (this->background2.getPosition().y == target->getSize().y)
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
