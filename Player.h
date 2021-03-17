#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include "Game.h"
#include "Enemy.h"
#include "Bullet.h"

using namespace sf;
using namespace std;

class Player
{
private:

	Sprite player;
	Texture playerTexture;

	float movementSpeed;
	int hp;
	int hpMax;

	void initVariables();
	void initPlayer();


public:
	Player(float x = 580.f, float y = 620.f);
	virtual ~Player();


	void updateInput();
	void updateWindowBundsCollision(const RenderTarget* target);
	void update(const RenderTarget* target);
	void render(RenderTarget* target);

};

