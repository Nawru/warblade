#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>

using namespace sf;
using namespace std;

class Bullet
{
private:

	Sprite bullet;

	Vector2f direction;

	float bulletStrenght;
	float bulletSpeed;
	string bulletType;

	void setBulletPosition(float x, float y);

	Texture defaultTexture;
	Texture redTexture;

public:


	Bullet(float pos_x, float pos_y, string type, string genus);
	virtual ~Bullet();

	const float getBulletStrenght() const;
	const string getBulletType() const;

	const Vector2f getBulletPos() const;
	const FloatRect getBulletBounds() const;

	void update(const float& dt);
	void render(RenderTarget *target);

};

#endif