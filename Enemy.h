#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Bullet.h"

using namespace sf;
using namespace std;

class Enemy
{
private:

	Sprite enemy;
	Texture enemyTexture;

	Vector2f direction;

	void initEnemy();
	void setEnemyPosition(float x, float y);

	int enemyStrenght = 1;
	int enemyType = 1;
	int enemyHp = 1;
	int enemyHpMax = 1;
	float enemySpeed = 1.f;

public:


	Enemy(float pos_x, float pos_y, float dir_x, float dir_y, int type);
	virtual ~Enemy();

	const int& getEnemyHp() const;
	const int& getEnemyHpMax() const;
	const int& getEnemyStrenght() const;

	const Vector2f getEnemyPos() const;
	const FloatRect getEnemyBounds() const;

	void update();
	void render(RenderTarget* target);

};