#pragma once

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
#include "Bullet.h"

using namespace sf;
using namespace std;

class Enemy
{
private:

	Sprite enemy;
	Texture enemyTexture;

	Vector2f direction;
	Vector2f c_direction;

	random_device rd;

	float cosinus = 0;
	float sinus = 0;
	bool enemyLeftAnimation = false;
	bool enemyRightAnimation = false;

	void initEnemy();
	void setEnemyPosition(float x, float y);

	int enemyStrenght = 1;
	int enemyType = 1;
	int enemyHp = 1;
	int enemyHpMax = 1;
	float enemySpeed = 1.f;

public:


	Enemy(float pos_x, float pos_y, int type);
	virtual ~Enemy();

	const int& getEnemyHp() const;
	const int& getEnemyHpMax() const;
	const int& getEnemyStrenght() const;

	void removeEnemyHp(int hp);
	

	const Vector2f getEnemyPos() const;
	const FloatRect getEnemyBounds() const;

	void update(RenderTarget* target);
	void render(RenderTarget* target);

};