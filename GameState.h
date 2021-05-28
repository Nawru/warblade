#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

class GameState :
    public State
{
private:

	//Game
	bool gameOver = false;
	int level = 1;
	ULONGLONG currentTime;

    // Player
    Player* player;
    void initPlayer(RenderTarget* target);
    void updatePlayer(const float& dt);

	//Background
	Background* background;
	void initBackground();
	void updateBackground(RenderTarget* target, const float& dt);

	//Gui
	Gui* gui;

	//Sounds
	GameSound* gameSound;

	//Events
	Event event;
	void updateInput(RenderTarget* target, const float& dt);

	//Bullets
	vector<Bullet*> bullets;
	void initBullet(float pos_x, float pos_y, string type, string genus);
	void updateBullets(const float& dt);

	//Enemies
	vector<Enemy*> enemies;
	void initEnemy();
	void updateEnemies(RenderTarget* target, const float& dt);
	int spawnEnemyCooldownInMillis = 400;
	int firstEnemySpawnTime;
	int secondEnemySpawnTime;

	//Colisionsz
	void updateBulletOutside(RenderTarget* target);
	void updateEnemyOutside(RenderTarget* target);
	void updateBulletPlayer(RenderTarget* target);
	void updateBulletEnemy(RenderTarget* target);

public:

    GameState(RenderWindow* window);
    virtual ~GameState();

    //Functions
    void endState();

	void updateMousePosition();

	void checkForQuit();

    void update(RenderTarget* target, const float& dt);
    void render(RenderTarget* target);

};

#endif
