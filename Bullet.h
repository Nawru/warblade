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

	Vector2f direction;

	void setBulletPosition(float x, float y);
	Texture defaultTexture;
	Texture redTexture;

public:


	Bullet(float pos_x, float pos_y, string type, string genus);
	virtual ~Bullet();

	int bulletStrenght;
	float bulletSpeed;
	string bulletType;

	const Vector2f getBulletPos() const;
	const FloatRect getBulletBounds() const;

	void update();
	void render(RenderTarget *target);

};

