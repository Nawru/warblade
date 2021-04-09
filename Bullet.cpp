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

Bullet::Bullet(float pos_x, float pos_y, string type, string genus)
{
	textures["DEFAULTBULLET"] = new Texture();
	textures["DEFAULTBULLET"]->loadFromFile("Textures/DefaultBulletTexture.png");

	textures["REDBULLET"] = new Texture();
	textures["REDBULLET"]->loadFromFile("Textures/RedBulletTexture.png");

	this->bulletType = type;
	this->setBulletPosition(pos_x, pos_y);
	if (this->bulletType == "enemyShot")
	{
		this->direction.x = 0.f;
		this->direction.y = 1.f;
		{
			this->bulletSpeed = 10;
			this->bullet.setTexture(*textures["DEFAULTBULLET"]);
			this->bullet.scale(0.2, 0.2);
		}
	}
	if (this->bulletType == "playerShot")
	{
		this->direction.x = 0.f;
		this->direction.y = -1.f;
		if (genus == "default")
		{
			this->bulletSpeed = 20;
			this->bullet.setTexture(*textures["REDBULLET"]);
			this->bullet.scale(0.2, 0.2);
		}
	}
}

Bullet::~Bullet()
{
	;
}


void Bullet::setBulletPosition(float x, float y)
{
	//this->bullet.setPosition(x - (this->bullet.getGlobalBounds().width / 2), (y - this->bullet.getGlobalBounds().height));
	this->bullet.setPosition(x, y);
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
