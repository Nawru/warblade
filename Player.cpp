#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

using namespace sf;
using namespace std;

Player::Player(float x, float y)
{
	this->player.setPosition(x, y);
	this->initVariables();
	this->initPlayer();
}

Player::~Player()
{
	;

}

void Player::initVariables()
{
	this->movementSpeed = 10.f;
}


void Player::initPlayer()
{

	if (!this->playerTexture.loadFromFile("playerTexture.png"))
	{
		cout << "LOAD PLAYER TEXTURE FAILED" << endl;
		system("pause");
	}
	this->player.setTexture(this->playerTexture);

	this->player.scale(0.2, 0.2);

	//this->player.setTextureRect(IntRect(0, 0, 64, 64));

}



void Player::updateInput()
{
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		this->player.move(-(this->movementSpeed), 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		this->player.move((this->movementSpeed), 0.f);
	}

	/*
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		this->player.move(0.f, -(this->movementSpeed));
	}
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		this->player.move(0.f, this->movementSpeed);
	}
	*/

	if (Keyboard::isKeyPressed(Keyboard::LControl))
	{
		// TODO strzelanie
	}
}

void Player::updateWindowBundsCollision(const RenderTarget* target)
{
	FloatRect playerBounds = this->player.getGlobalBounds();
	int windowWidth = target->getSize().x;

	// Kolizja gracza z lewą krawędzią ekranu
	if (playerBounds.left <= 0.f)
		player.setPosition(0.f, playerBounds.top);

	// kolizja gracza z prawą krawędzią ekranu
	if ((playerBounds.left + playerBounds.width) >= windowWidth)
		player.setPosition(windowWidth - playerBounds.width, playerBounds.top);


}


void Player::update(const RenderTarget *target)
{
	this->updateInput();
	this->updateWindowBundsCollision(target);
}

void Player::render(RenderTarget* target)
{
	target->draw(this->player);
}
