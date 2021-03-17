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

	int hp;
	int hpMax;

	void initVariables();
	void initEnemy();

public:

	Enemy();
	virtual ~Enemy();

	void update();
	void render(RenderTarget& target);
};

