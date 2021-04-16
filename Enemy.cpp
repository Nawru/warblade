#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <math.h>
#include <random>
#include "Game.h"
#include "Player.h"
#include "Enemy.h"

using namespace sf;
using namespace std;

Enemy::Enemy(float pos_x, float pos_y, int type)
{
	this->initEnemy();
	this->setEnemyPosition(pos_x, pos_y);
	this->direction.x = 0;
	mt19937 rng(rd());
	uniform_int_distribution<> gen(10, 30);
	this->direction.y = gen(rng) / 10;
	this->c_direction.x = this->direction.x;
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

	this->enemy.scale(0.3, 0.3);
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
void Enemy::removeEnemyHp(int hp)
{
	this->enemyHp -= hp;
}
void Enemy::update(RenderTarget* target)
{
	mt19937 rng(rd());
	uniform_int_distribution<> gen(0, 20);

	if (gen(rng) == 1)
		if (this->enemyLeftAnimation == false && this->enemyRightAnimation == false)
		{
			this->enemyLeftAnimation = true;
		}
	if (gen(rng) == 2)
		if (this->enemyLeftAnimation == false && this->enemyRightAnimation == false)
		{
			this->enemyRightAnimation = true;
		}

	if (this->enemyLeftAnimation == true)
	{
		if (this->sinus >= 0 && this->sinus < 1.57)
		{
			this->direction.x = -(0.5 * sin(this->sinus));
			this->sinus += 0.05;
		}
		else if(this->sinus >= 1.57 && this->sinus <= 3.14)
		{
			this->direction.x = -(0.5 * sin(this->sinus));
			this->sinus += 0.05;
		}
		if (this->sinus >= 3.14)
		{
			this->sinus = 0.f;
			this->direction.x = 0.f;
			this->enemyLeftAnimation = false;
		}
	}
	if (this->enemyRightAnimation == true)
	{
		if (this->sinus >= 0 && this->sinus < 1.57)
		{
			this->direction.x = (0.5 * sin(this->sinus));
			this->sinus += 0.05;
		}



		else if (this->sinus >= 1.57 && this->sinus <= 3.14)
		{
			this->direction.x = (0.5 * sin(this->sinus));
			this->sinus += 0.05;
		}

		if (this->sinus > 3.14)
		{
			this->sinus = 0.f;
			this->direction.x = 0.f;
			this->enemyLeftAnimation = false;
		}
	}
	this->enemy.move(this->enemySpeed * this->direction);
}

void Enemy::render(RenderTarget* target)
{
	target->draw(this->enemy);
}
