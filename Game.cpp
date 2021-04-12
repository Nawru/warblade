#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <string>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>

#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "GameSound.h"
#include "Gui.h"
#include "Background.h"
#include "Gui.h"


using namespace sf;
using namespace std;



Game::Game()
{

	this->initVariables(); cout << "Variables loaded." << endl;
	this->initWindow(); cout << "Window created." << endl;
	this->initPlayer(); cout << "Player created." << endl;

}

Game::~Game()
{

	delete this->window;
	delete this->player;
	delete this->background;
	delete this->gameSound;
	delete this->gui;

	for (auto* bullet : this->bullets)
	{
		delete bullet;
	}
	for (auto* enemy : this->enemies)
	{
		delete enemy;
	}

}

const bool Game::running() const
{
	// Return window open (true or false)
	return this->window->isOpen();
}

//////////////////////////////////////////////////
//
//				INIT SECTION 
//
//////////////////////////////////////////////////

void Game::initVariables()
{

	this->window = nullptr;
	this->gameSound = new GameSound();
	this->background = new Background();
	this->gui = new Gui();

	this->gameSound->playMusic("backgroundMusic", 2);

}


void Game::initWindow()
{

	this->videoMode.height = 720;
	this->videoMode.width = 1280;
	
	this->window = new RenderWindow(this->videoMode, "Warblade project by Roman Nawrot", Style::Titlebar | Style::Close | Style::Resize);

	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);

}

void Game::initPlayer()
{
	this->player = new Player();
	this->player->setPosition(this->window);
}

void Game::initBullet(float pos_x, float pos_y, string type, string genus)
{
	this->bullets.push_back(
		new Bullet(
			/* Srodkowa pozycja gracza x			*/	pos_x,
			/* Gorna pozycja gracza y				*/	pos_y,
			/* Typ pocisku	(1 - enemy, 2 - player)	*/	type,
			/* Rodzaj pocisku						*/	genus	
		)
	);
}

void Game::initEnemy()
{
	this->enemies.push_back(
		new Enemy(
			/* lewy gorny rog enemy x		*/	(rand() % 800) + 200,
			/* lewy gorny rog enemy y		*/	-100,
			/* Kierunek lotu x				*/	(rand() % 3) - 1,
			/* Kierunek lotu y			    */	(rand() % 3) + 1,
			/* Typ enemy				    */	4
		)
	);
}

//////////////////////////////////////////////////
//
//				UPDATE SECTION 
//
//////////////////////////////////////////////////

void Game::updatePlayer()
{
	this->player->update();
}


void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();
		counter++;
	}
}

void Game::updateEnemies()
{
	if (spawnTimer > spawnTimerMax)
	{
		this->initEnemy();
		this->spawnTimer = 0;
	}
	else
	{
		this->spawnTimer++;
	}

	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update();

		if ((rand() % 10) == 1)
		{
			this->initBullet((enemy->getEnemyPos().x + (enemy->getEnemyBounds().width / 2)), (enemy->getEnemyPos().y + enemy->getEnemyBounds().height + 51), "enemyShot", "default");
		}
		counter++;
	}
}

void Game::updateInput()
{
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		this->player->playerMove(this->window, -1.f, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		this->player->playerMove(this->window, 1.f, 0.f);
	}

	/*
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		this->player->playerMove(0.f, -1.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		this->player->playerMove(0.f, 1.f);
	}
	*/

	///////////// STRZELANIE ////////////

	if (Keyboard::isKeyPressed(Keyboard::LControl))
	{
		if (this->player->canAttack())
		{
			this->initBullet((this->player->getPlayerPos().x + (this->player->getPlayerBounds().width / 2.f)), (this->player->getPlayerPos().y), "playerShot", "default");
			this->gameSound->playSound("bulletShot", 1);
		}
	}
}

void Game::updateWindowEvent()
{
	while (this->window->pollEvent(this->event))
	{
		if (this->event.type == Event::Closed)
		{
			this->window->close(); // Jezeli eventem wykonanym na oknie bedzie wcisniecie czerwonego x, zostanie zamkniete okno
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			this->window->close();
		}
	}
}


void Game::updateBulletOutside()
{

	unsigned counter_bullet = 0;
	bool bullet_deleted = false;

	//////////////////////////////////
	//
	// Bullet usuwany po przekroczeniu
	// gornej i dolnej granicy ekranu
	//
	//////////////////////////////////


	for (auto* bullet : this->bullets)
	{
		if (((bullet->getBulletPos().y < -(bullet->getBulletBounds().height)) ||
			(bullet->getBulletPos().y > this->window->getSize().y)) 
			&& bullet_deleted == false )
		{

			delete this->bullets.at(counter_bullet);
			cout << "BULLET OUTSIDE: BULLET DELETED AT " << counter_bullet << endl;

			this->bullets.erase(this->bullets.begin() + counter_bullet);
			cout << "BULLET OUTSIDE: VECTOR BULLET DELETED AT " << counter_bullet << endl;

			bullet_deleted = true;

		}
		++counter_bullet;
	}
}

void Game::updateEnemyOutside()
{

	bool enemy_deleted = false;
	unsigned counter_enemy = 0;

	//////////////////////////////////
	//
	// Enemy usuwany po przekroczeniu
	// granic ekranu
	//
	//////////////////////////////////

	for (auto* enemy : this->enemies)
	{

		if ((
			enemy->getEnemyPos().x > this->window->getSize().x ||			//Enemy poza prawa krawedzia ekranu
			enemy->getEnemyPos().x < -(enemy->getEnemyBounds().width) ||	//Enemy poza lewa krawedzia ekranu
			enemy->getEnemyPos().y > this->window->getSize().y )			//Enemy poza dolna krawedzia ekranu
			&& enemy_deleted == false)			
		{

			delete this->enemies.at(counter_enemy);
			cout << "ENEMY OUTSIDE: ENEMY DELETED AT " << counter_enemy << endl;

			this->enemies.erase(this->enemies.begin() + counter_enemy);
			cout << "ENEMY OUTSIDE: VECTOR ENEMY DELETED AT " << counter_enemy << endl;

			enemy_deleted = true;

		}

		++counter_enemy;
	}
}

void Game::updateBulletPlayer()
{
	unsigned counter_bullet = 0;
	bool bullet_deleted = false;

	//////////////////////////////////
	//
	// Bullet od enemy i player 
	// usuwani po zderzeniu sie
	//
	//////////////////////////////////

	for (auto* bullet : this->bullets)
	{

		if (bullet->getBulletBounds().intersects(this->player->getPlayerBounds()))
		{
			if (bullet->bulletType == "enemyShot" &&  // jezeli bullet jest od enemy
				bullet_deleted == false )
			{

				///////////////////////////////////////////////////

				// CO SIE DZIEJE PO TRAFIENIU POCISKU ENEMY W GRACZA


				delete this->bullets.at(counter_bullet);   //  Usuwanie dynamicznie utworzonego bulleta
				cout << "BULLET->PLAYER: BULLET DELETED AT " << counter_bullet << endl;

				this->bullets.erase(this->bullets.begin() + counter_bullet);   //  usuwanie bulleta z wektora
				cout << "BULLET->PLAYER: VECTOR BULLET DELETED AT " << counter_bullet << endl;

				bullet_deleted = true;

				this->gameSound->playSound("killPlayer", 1);

				if (this->player->getPlayerHp() > 0)
				{
					this->player->removeHp(1);
					this->gui->setGUIhp(this->player->getPlayerHp());
				}

				cout << "HP: " << this->player->getPlayerHp() << endl;

				if (this->player->getPlayerHp() <= 0)
				{
					cout << "DED" << endl;
					this->gui->renderGameOver();
					this->gameOver = true;
					this->gameSound->pauseMusic("backgroundMusic");
				}
				///////////////////////////////////////////////////

			}
		}
		++counter_bullet;
	}
}

void Game::updateBulletEnemy()
{
	unsigned counter_bullet = 0;

	unsigned counter_enemy = 0;
	bool bullet_deleted = false;

	//////////////////////////////////
	//
	// Enemy usuwany po zdrzeneniu z
	// bulletem gracza, bullet usuwany
	//
	//////////////////////////////////

	for (auto* bullet : this->bullets)
	{
		bool enemy_deleted = false;
		counter_enemy = 0;
		for (auto* enemy : this->enemies)
		{
			if (bullet->getBulletBounds().intersects(enemy->getEnemyBounds())) // Sprawdzanie czy bullet trafil w enemy 
			{
				if (bullet->bulletType != "enemyShot"  // jesli bullet nie jest od enemy (zeby enemy nie zabijali enemy)
					&& enemy_deleted == false 
					&& bullet_deleted == false )
				{

					///////////////////////////////////////////////
					// 
					//	CO SIE DZIEJE PO TRAFIENIU BULLETA W ENEMY
					//
					//
					delete this->bullets.at(counter_bullet);
					cout << "BULLET->ENEMY: BULLET DELETED AT " << counter_bullet << endl;
					this->bullets.erase(this->bullets.begin() + counter_bullet);
					cout << "BULLET->ENEMY: BULLET VECTOR DELETED AT " << counter_bullet << endl;
					bullet_deleted = true;
					//
					delete this->enemies.at(counter_enemy);
					cout << "BULLET->ENEMY: ENEMY DELETED AT " << counter_enemy << endl;
					this->enemies.erase(this->enemies.begin() + counter_enemy);
					cout << "BULLET->ENEMY: VECTOR ENEMY DELETED AT " << counter_enemy << endl;
					enemy_deleted == true;
					//
					//
					this->gameSound->playSound("killEnemy", 1);
					this->player->addPoints(10);
					this->gui->setGUIpoints(this->player->getPoints());
					cout << "Points: " << this->player->getPoints() << endl;
					//
					/////////////////////////////////////////////////
				}
			}
			++counter_enemy;
		}
		++counter_bullet;
	}
}

void Game::update()
{
	this->updateWindowEvent();
	if (gameOver == false)
	{
		this->updateInput();
		this->updatePlayer();
		this->updateBullets();
		this->updateEnemies();
		this->updateBulletEnemy();
		this->updateBulletOutside();
		this->updateBulletPlayer();
		this->updateEnemyOutside();
	}
	this->background->updateBackground(this->window);
}

//////////////////////////////////////////////////
//
//				 RENDER SECTION 
//
//////////////////////////////////////////////////

void Game::render()
{
	this->window->clear();  // Clear window

	this->background->renderBackground(this->window);  // Render world (background)

	this->player->render(this->window);  // Render player

	// Render enemies
	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	// Render bullets
	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	this->gui->reder(this->window);

	// Display all objects
	this->window->display();
}