#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <string>
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

	float attackCooldown;
	float attackCooldownMax;

	int hp;
	int hpMax;
	int points;
	int money;


	void initVariables();
	void initPlayer();


public:
	Player();
	virtual ~Player();

	const Vector2f& getPlayerPos() const;
	const FloatRect getPlayerBounds() const;
	const int& getPlayerHp() const;
	const int& getPlayerHpMax() const;
	const int getPoints() const;

	void setPosition(const RenderTarget* target);
	void removeHp(const int hp);
	void addHp(const int hp);
	void addPoints(const int points);

	void playerMove(const RenderTarget* target, const float dirX, const float dirY);
	const bool canAttack();
	void updateCooldownAttack();

	void update();
	void render(RenderTarget* target);

};

