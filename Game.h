#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

using namespace sf;
using namespace std;

class Game
{
private:

	//Window
	RenderWindow* window;
	VideoMode videoMode;
	void initWindow();
	void initVariables();

	//Events
	Event event;
	void updateInput();
	void pollEvents();

	//Bullets
	vector<Bullet*> bullets;
	void initBullet();
	void updateBullets();

	//Player
	Player* player;
	void initPlayer();
	void updatePlayer();

	//Enemies
	vector<Enemy*> enemies;
	void initEnemy();
	void updateEnemies();

	



public:

	Game(); //Constructor
	virtual ~Game(); //Destructor

	const bool running() const; //Check window running (true or false)

	// Functions
	void update();
	void render();
};