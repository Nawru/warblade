#pragma once

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

class Bullet
{
private:

	Sprite bullet;
	Texture bulletTexture;

	Vector2f direction;

	void initBullet();
	void setBulletPosition(float x, float y);

	int bulletType;
	int bulletStrenght;
	float bulletSpeed;

public:


	Bullet(float pos_x, float pos_y, float dir_x, float dir_y, int type);
	virtual ~Bullet();



	const Vector2f getBulletPos() const;
	const FloatRect getBulletBounds() const;

	void update();
	void render(RenderTarget *target);

};

