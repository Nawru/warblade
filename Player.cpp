#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <string>
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

using namespace sf;
using namespace std;



Player::Player()
{
	this->initVariables();
	this->initPlayer();

	cout << "Created player object" << endl;
	cout << "HP: " << this->hp << endl;

}

Player::~Player()
{
	;

}

void Player::initVariables()
{
	this->movementSpeed = 10.f;
	this->attackCooldownMax = 5;
	this->attackCooldown = this->attackCooldownMax;
	this->hpMax = 100;
	this->hp = this->hpMax;
	this->points = 0;


	cout << "Initializated player variables" << endl;

}


void Player::initPlayer()
{

	if (!this->playerTexture.loadFromFile("Textures/playerTexture.png"))
	{
		cout << "LOAD PLAYER TEXTURE FAILED" << endl;
		system("pause");
	}

	this->player.setTexture(this->playerTexture);

	this->player.scale(0.2, 0.2);

	cout << "Player texture loaded" << endl;

	//this->player.setTextureRect(IntRect(0, 0, 64, 64));

}

const Vector2f& Player::getPlayerPos() const
{
	return this->player.getPosition();
}

const FloatRect Player::getPlayerBounds() const
{
	return this->player.getGlobalBounds();
}

const int& Player::getPlayerHp() const
{
	return this->hp;
}

const int& Player::getPlayerHpMax() const
{
	return this->hpMax;
}

void Player::setPosition(const RenderTarget* target)
{

	/*
	
	Pozycja startowa gracza jest ustawiana na srodku osi x okna (szerokosci)
	oraz 30 pixeli nad dolną krawędzią okna
	
	*/

	this->player.setPosition(((target->getSize().x / 2) - (this->player.getGlobalBounds().width / 2)), (target->getSize().y - this->player.getGlobalBounds().height - 30));

	cout << "Player start position: " << (target->getSize().x / 2) - this->player.getGlobalBounds().width / 2 << ", " << (target->getSize().y) - this->player.getGlobalBounds().height - 30 << endl;
}

void Player::removeHp(const int hp)
{
	this->hp -= hp;
}

void Player::addHp(const int hp)
{
	this->hp += hp;
}

void Player::addPoints(const int points)
{
	this->points += points;
}

const int Player::getPoints() const
{
	return this->points;
}

void Player::playerMove(const RenderTarget* target, const float dirX, const float dirY)
{ 
	if (this->player.getPosition().x > 0.f)
	{
		if ((this->player.getPosition().x + this->player.getGlobalBounds().width) < target->getSize().x)
		{
			this->player.move((this->movementSpeed * dirX), (this->movementSpeed * dirY));
		}
		else if (dirX < 0)
		{
			this->player.move((this->movementSpeed * dirX), (this->movementSpeed * dirY));
		}
	}
	else if (dirX > 0)
	{
		this->player.move((this->movementSpeed * dirX), (this->movementSpeed * dirY));
	}
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}

	return false;
}

void Player::updateCooldownAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;
}

void Player::update()
{
	this->updateCooldownAttack();
}

void Player::render(RenderTarget* target)
{
	target->draw(this->player);

}
