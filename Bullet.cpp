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

Bullet::Bullet(float pos_x, float pos_y, float dir_x, float dir_y, int type)
{
	this->initBullet();
	this->setBulletPosition(pos_x, pos_y);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	if (type == 1)
		bulletSpeed = 10;
	if (type == 2)
		bulletSpeed = 15;
	if (type == 3)
		bulletSpeed = 20;
	if (type == 4)
		bulletSpeed = 25;
}

Bullet::~Bullet()
{
	;
}

void Bullet::initBullet()
{
	if (!this->bulletTexture.loadFromFile("Textures/bulletTexture.png"))
	{
		cout << "LOAD BULLET TEXTURE FAILED" << endl;
		system("pause");
	}
	this->bullet.setTexture(this->bulletTexture);

	this->bullet.scale(0.2, 0.2);
}


void Bullet::setBulletPosition(float x, float y)
{
	this->bullet.setPosition(x - (bullet.getGlobalBounds().width / 2), y - 40);
}


const Vector2f Bullet::getBulletPos() const
{
	return this->bullet.getPosition();
}

const FloatRect Bullet::getBulletBounds() const
{
	return this->bullet.getGlobalBounds();
}

void Bullet::update()
{
	this->bullet.move(this->bulletSpeed * this->direction);
}

void Bullet::render(RenderTarget *target)
{
	target->draw(this->bullet);
}
