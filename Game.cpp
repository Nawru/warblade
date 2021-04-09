#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <string>
#include <iostream>
#include <cmath>
#include <cstdlib>

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


// INIT SECTION 


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


// UPDATE SECTION 


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
		if (
			enemy->getEnemyPos().x > this->window->getSize().x ||		//Enemy poza prawa krawedzia ekranu
			enemy->getEnemyPos().x < -(enemy->getEnemyBounds().width) ||	//Enemy poza lewa krawedzia ekranu
			enemy->getEnemyPos().y > this->window->getSize().y			//Enemy poza dolna krawedzia ekranu
			)
		{
			//Delete enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		counter++;
		if ((rand() % 10) == 1)
		{
			this->initBullet((enemy->getEnemyPos().x + (enemy->getEnemyBounds().width / 2)), (enemy->getEnemyPos().y + enemy->getEnemyBounds().height + 51), "enemyShot", "default");
		}
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

	/////////////////////////////////////

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


void Game::updateCollision()
{
	unsigned counter_bullet = 0;
	bool bullet_deleted;
	for (auto* bullet : this->bullets)
	{
		bullet_deleted = false;
		if (

			//////////////////////////////////////////////////////

			//		SPRAWDZANIE CZY BULLET TRAFIL W PLAYER		//

			bullet->getBulletPos().x >= (this->player->getPlayerPos().x - bullet->getBulletBounds().width) &&
			bullet->getBulletPos().x <= (this->player->getPlayerPos().x + this->player->getPlayerBounds().width) &&

			bullet->getBulletPos().y <= (this->player->getPlayerPos().y + this->player->getPlayerBounds().height) &&
			bullet->getBulletPos().y >= (this->player->getPlayerPos().y - bullet->getBulletBounds().height)

			/////////////////////////////////////////////////////

			)

		{
			if (bullet->bulletType == "enemyShot") // jezeli bullet jest od enemy
			{

				///////////////////////////////////////////////////

				// CO SIE DZIEJE PO TRAFIENIU POCISKU ENEMY W GRACZA

				if (bullet_deleted == false)
				{
					delete this->bullets.at(counter_bullet);   //  Usuwanie dynamicznie utworzonego bulleta
					this->bullets.erase(this->bullets.begin() + counter_bullet);   //  usuwanie bulleta z wektora
					bullet_deleted = true;
				}


				if (this->player->getPlayerHp() > 0)
				{
					this->player->removeHp(1);  // zmniejszanie hp player o tyle ile Strenght ma enemy
					this->gui->setGUIhp(this->player->getPlayerHp());
				}

				cout << "HP: " << this->player->getPlayerHp() << endl;

				if (this->player->getPlayerHp() <= 0)
				{
					cout << "DED" << endl;
					this->gui->renderGameOver();
					//this->gameOver = true;
				}

				///////////////////////////////////////////////////

			}
		}

		if (bullet->getBulletPos().y < -(bullet->getBulletBounds().height)) // jezeli gorna krawedz grafiki pocisku jest nizej niz wysokosc grafiki nad ekranem
		{
			//Delete bullet
			if (bullet_deleted == false)
			{
				delete this->bullets.at(counter_bullet);
				this->bullets.erase(this->bullets.begin() + counter_bullet);
				bullet_deleted = true;
			}
		}

		unsigned counter_enemy = 0;

		for (auto* enemy : this->enemies)
		{
			if (

				// Sprawdzanie czy bullet trafil w enemy 

				bullet->getBulletPos().x >= (enemy->getEnemyPos().x - bullet->getBulletBounds().width) &&
				bullet->getBulletPos().x <= (enemy->getEnemyPos().x + enemy->getEnemyBounds().width) &&

				bullet->getBulletPos().y <= (enemy->getEnemyPos().y + enemy->getEnemyBounds().height) &&
				bullet->getBulletPos().y >= (enemy->getEnemyPos().y - bullet->getBulletBounds().height)

				)
			{
				if (bullet->bulletType != "enemyShot") // jesli bullet nie jest od enemy
				{

					///////////////////////////////////////////////

					//	CO SIE DZIEJE PO TRAFIENIU BULLETA W ENEMY

					if (bullet_deleted == false)
					{
						delete this->bullets.at(counter_bullet);
						this->bullets.erase(this->bullets.begin() + counter_bullet);
						bullet_deleted = true;
					}

					delete this->enemies.at(counter_enemy);
					this->enemies.erase(this->enemies.begin() + counter_enemy);

					this->gameSound->playSound("killEnemy", 1);
					this->player->addPoints(10);
					this->gui->setGUIpoints(this->player->getPoints());
					cout << "Points: " << this->player->getPoints() << endl;

					/////////////////////////////////////////////////

				}


			}

			counter_enemy++;

		}

		counter_bullet++;
	}
}

void Game::update()
{

	this->updateInput();
	this->updatePlayer();
	this->updateBullets();
	this->updateEnemies();
	this->updateCollision();
	this->background->updateBackground(this->window);

}


//////////////////////////////////////////////////


// RENDER SECTION 


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