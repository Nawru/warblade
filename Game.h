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
	void renderWorld();
	Sprite background1;
	Sprite background2;
	Texture backbroundTexture;

	//Sounds
	Music* music;
	SoundBuffer bufferShotSound;
	SoundBuffer bufferEnemySound;
	Sound* bulletShotSound;
	Sound* killEnemySound;
	void initMusic();
	void initSounds();
	void updateMusic();
	void updateSounds(string type);

	//Events
	Event event;
	void updateInput();
	void pollEvents();

	//Bullets
	vector<Bullet*> bullets;
	void initBullet(string type, float pos_x, float pos_y);
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

	//Colisions
	void checkCollision();


public:

	Game(); //Constructor
	virtual ~Game(); //Destructor

	const bool running() const; //Check window running (true or false)

	// Functions
	void update();
	void render();
};