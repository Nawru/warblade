#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Enemy.h"

using namespace sf;
using namespace std;

Enemy::Enemy(float pos_x, float pos_y, float dir_x, float dir_y, int type)
{
	this->initEnemy();
	this->setEnemyPosition(pos_x, pos_y);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	if (type == 1)
	{
		this->enemySpeed = 1;
		this->enemyStrenght = 1;
	}
	if (type == 2)
	{
		this->enemySpeed = 2;
		this->enemyStrenght = 2;
	}
	if (type == 3)
	{
		this->enemySpeed = 3;
		this->enemyStrenght = 3;
	}
	if (type == 4)
	{
		this->enemySpeed = 4;
		this->enemyStrenght = 4;
	}

}

Enemy::~Enemy()
{
	;
}



void Enemy::initEnemy()
{
	if (!this->enemyTexture.loadFromFile("Textures/enemyTexture.png"))
	{
		cout << "LOAD ENEMY TEXTURE FAILED" << endl;
		system("pause");
	}
	this->enemy.setTexture(this->enemyTexture);

	this->enemy.scale(0.2, 0.2);
}

void Enemy::setEnemyPosition(float x, float y)
{
	this->enemy.setPosition(x, y);
}


const Vector2f Enemy::getEnemyPos() const
{
	return this->enemy.getPosition();

}

const FloatRect Enemy::getEnemyBounds() const
{
	return this->enemy.getGlobalBounds();

}

const int& Enemy::getEnemyHp() const
{
	return this->enemyHp;
}

const int& Enemy::getEnemyHpMax() const
{
	return this->enemyHpMax;
}
const int& Enemy::getEnemyStrenght() const
{
	return this->enemyStrenght;
}
void Enemy::update()
{
	this->enemy.move(this->enemySpeed * this->direction);
}

void Enemy::render(RenderTarget* target)
{
	target->draw(this->enemy);
}
