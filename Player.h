#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>

using namespace sf;
using namespace std;

class Player
{
private:

	Sprite player;
	Texture playerTexture;

	float movementSpeed;

	int attackCooldownInMillis;

	int hp;
	int hpMax;
	int points;
	int money;
	int level;

	void initVariables();
	void initPlayer();

public:

	Player();
	virtual ~Player();

	const Vector2f& getPlayerPos() const;
	const FloatRect getPlayerBounds() const;
	const int& getPlayerHp() const;
	const int& getPlayerHpMax() const;
	const int& getPoints() const;
	const int& getLevel() const;

	void setPosition(const RenderTarget* target);
	void removeHp(const int hp);
	void addHp(const int hp);
	void addPoints(const int points);
	void setLevel(const int level);

	void playerMove(const RenderTarget* target, const float& dt, const float dirX, const float dirY);

	bool canAttack;
	void updateCooldownAttack();
	int firstAttackTime;
	int secondAttackTime;

	void update(const float& dt);
	void render(RenderTarget* target);

};

#endif