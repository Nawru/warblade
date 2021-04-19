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

	this->bulletType = type;

	if (this->bulletType == "enemyShot")
	{
		this->direction.x = 0.f;
		this->direction.y = 1.f;
		if (!defaultTexture.loadFromFile("Textures/DefaultBulletTexture.png"))
		{
			cout << "LOAD ENEMY TEXTURE FAILED" << endl;
		}
		this->bulletSpeed = 10;
		this->bullet.setTexture(defaultTexture);
		this->bullet.scale(0.1f, 0.1f);
		this->bulletStrenght = 1;
	}
	if (this->bulletType == "playerShot")
	{
		this->direction.x = 0.f;
		this->direction.y = -1.f;
		if (genus == "default")
		{
			if (!redTexture.loadFromFile("Textures/RedBulletTexture.png"))
			{
				cout << "LOAD ENEMY TEXTURE FAILED" << endl;
			}
			this->bulletSpeed = 20;
			this->bullet.setTexture(redTexture);
			this->bullet.scale(0.1, 0.1);
			this->bulletStrenght = 1;
		}
	}

	this->bullet.setPosition(pos_x - (this->bullet.getGlobalBounds().width / 2), (pos_y - this->bullet.getGlobalBounds().height));
}

Bullet::~Bullet()
{
	;
}


void Bullet::setBulletPosition(float x, float y)
{
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
