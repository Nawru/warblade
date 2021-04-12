#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <vector>

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Background.h"
#include "GameSound.h"
#include "Gui.h"

using namespace sf;
using namespace std;

class Game
{
private:

	//Game
	bool gameOver = false;
	int level = 1;

	//Window
	RenderWindow* window;
	VideoMode videoMode;
	void initWindow();
	void initVariables();

	//Background
	Background* background;

	//Gui
	Gui* gui;

	//Sounds
	GameSound* gameSound;

	//Events
	Event event;
	void updateInput();
	void updateWindowEvent();

	//Bullets
	vector<Bullet*> bullets;
	void initBullet(float pos_x, float pos_y, string type, string genus);
	void updateBullets();

	//Player
	Player* player;
	void initPlayer();
	void updatePlayer();

	//Enemies
	vector<Enemy*> enemies;
	void initEnemy();
	void updateEnemies();
	int spawnTimer;
	int spawnTimerMax = 50;

	//Colisionsz
	//void updateCollision();
	void updateBulletOutside();
	void updateEnemyOutside();
	void updateBulletPlayer();
	void updateBulletEnemy();


public:

	Game();
	virtual ~Game();

	const bool running() const;

	void update();
	void render();
};