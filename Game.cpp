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


using namespace sf;
using namespace std;

Game::Game()
{

	this->initVariables();
	this->initWindow();
	this->initPlayer();
	this->initEnemy();
	this->initMusic();
	this->initSounds();

}

Game::~Game()
{

	// Destruktor usuwa ekran

	delete this->window;
	delete this->player;
	delete this->music;
	delete this->bulletShotSound;
	delete this->killEnemySound;

	for (auto* i : this->bullets)
	{
		delete i;
	}
	for (auto* i : this->enemies)
	{
		delete i;
	}

}

const bool Game::running() const
{
	// Return window open (true or false)
	return this->window->isOpen();
}

void Game::pollEvents()
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



void Game::initMusic()
{
	this->music = new Music();
	if (!this->music->openFromFile("Sounds\\backgroundMusic.ogg"))
	{
		cout << "LOAD MUSIC FROM FILE ERROR" << endl;
	}
	this->music->setLoop(true);
	this->music->setVolume(8.f);
	this->music->play();

}




void Game::initSounds()
{

	this->bulletShotSound = new Sound();
	this->killEnemySound = new Sound();
	if (!this->bufferShotSound.loadFromFile("Sounds\\bulletShotSound.wav"))
	{
		cout << "LOAD BULLET SOUND FROM FILE ERROR" << endl;
	}
	this->bulletShotSound->setBuffer(this->bufferShotSound);
	this->bulletShotSound->setVolume(2.f);
	if (!this->bufferEnemySound.loadFromFile("Sounds\\killEnemySound.wav"))
	{
		cout << "LOAD KILL ENEMY SOUND FROM FILE ERROR" << endl;
	}
	this->killEnemySound->setBuffer(this->bufferEnemySound);
	this->killEnemySound->setVolume(2.f);
	
}


void Game::updateMusic()
{
}





void Game::updateSounds(string type)
{
	if (type == "bulletShot")
	{
		
		this->bulletShotSound->play();
	}
	if (type == "killEnemy")
	{
		
		this->killEnemySound->play();
	}
}



void Game::initVariables()
{

	// Wczytywanie ustawien ekranu

	this->window = nullptr;

}

void Game::initWindow()
{

	// Ustawianie rozdzielczosci ekranu, limit FPS, tytul ekranu, funkcje okna (możliwość zamykania)

	this->videoMode.height = 720;
	this->videoMode.width = 1280;
	
	this->window = new RenderWindow(this->videoMode, "Warblade project by Roman Nawrot", Style::Titlebar | Style::Close | Style::Resize);

	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);


	if (!this->backbroundTexture.loadFromFile("Textures/backgroundTexture.png"))
	{
		cout << "LOAD PLAYER TEXTURE FAILED" << endl;
		system("pause");
	}

	this->background1.setTexture(this->backbroundTexture);
	this->background1.setPosition(0.f, 0.f);
	this->background2.setTexture(this->backbroundTexture);
	this->background2.setPosition(0.f, -(this->background2.getGlobalBounds().height));

}

void Game::initPlayer()
{
	this->player = new Player();
	this->player->setPosition(this->window);
}

void Game::initBullet(string type, float pos_x, float pos_y)
{
	float dir_X = 0.f;
	float dir_Y = 0.f;
	int bullet_type = 1;
	if (type == "playerShot")
	{
		dir_X = 0.f;
		dir_Y = -1.f;
		bullet_type = 1;
	}
	if (type == "enemyShot")
	{
		dir_X = 0.f;
		dir_Y = 1.f;
		bullet_type = 1;
	}
	this->bullets.push_back(
		new Bullet(
			/* Srodkowa pozycja gracza x	*/	pos_x,
			/* Gorna pozycja gracza y		*/	pos_y,
			/* Kierunek lotu x				*/	dir_X,
			/* Kierunek lotu Y			    */	dir_Y,
			/* Typ pocisku				    */	bullet_type
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
			/* Typ enemy				    */	(rand() % 4)
		)
	);
}




void Game::checkCollision()
{
	unsigned counter_bullet = 0;
	for (auto* bullet : this->bullets)
	{
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
					delete this->enemies.at(counter_enemy);
					this->enemies.erase(this->enemies.begin() + counter_enemy);

					delete this->bullets.at(counter_bullet);
					this->bullets.erase(this->bullets.begin() + counter_bullet);

					this->updateSounds("killEnemy");
			}
			counter_enemy++;
		}
		if (
			// Sprawdzanie czy bullet trafił w player
			bullet->getBulletPos().x >= (this->player->getPlayerPos().x - bullet->getBulletBounds().width) &&
			bullet->getBulletPos().x <= (this->player->getPlayerPos().x + this->player->getPlayerBounds().width) &&

			bullet->getBulletPos().y <= (this->player->getPlayerPos().y + this->player->getPlayerBounds().height) &&
			bullet->getBulletPos().y >= (this->player->getPlayerPos().y - bullet->getBulletBounds().height)
			)
		{




			// TODO smierc gracza
			cout << "DED" << endl;
		}
		counter_bullet++;
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		if (bullet->getBulletPos().y  < (-bullet->getBulletBounds().height)) // jezeli gorna krawedz grafiki pocisku jest nizej niz wysokosc grafiki nad ekranem
		{
			//Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
		}

		counter++;
	}
}


void Game::updatePlayer()
{
	this->player->update();
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
			enemy->getEnemyPos().x > this->window->getSize().x ||	//Enemy poza prawa krawedzia ekranu
			enemy->getEnemyPos().x < enemy->getEnemyBounds().width ||	//Enemy poza lewa krawedzia ekranu
			enemy->getEnemyPos().y > this->window->getSize().y			//Enemy poza dolna krawedzia ekranu
			)
		{
			//Delete bullet
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		counter++;
		if ((rand() % 100) == 1)
		{
			this->initBullet("enemyShot", (enemy->getEnemyPos().x + (enemy->getEnemyBounds().width / 2)), (enemy->getEnemyPos().y + enemy->getEnemyBounds().height + 51));
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

	if (Keyboard::isKeyPressed(Keyboard::LControl))
	{
		if (this->player->canAttack())
		{
			this->initBullet("playerShot", (this->player->getPlayerPos().x + (this->player->getPlayerBounds().width / 2.f)), (this->player->getPlayerPos().y));
			this->updateSounds("bulletShot");
		}
	}
}

void Game::update()
{

	// Update window events
	this->pollEvents();
	this->updateInput();

	// Update objects
	this->updateBullets();
	this->updateEnemies();
	this->updatePlayer();

	// Checking collisions
	this->checkCollision();

}

void Game::renderWorld()
{
	if (this->background1.getPosition().y == this->window->getSize().y)
	{
		this->background1.setPosition(0.f, -(this->background1.getGlobalBounds().height));
	}
	if (this->background2.getPosition().y == this->window->getSize().y)
	{
		this->background2.setPosition(0.f, -(this->background2.getGlobalBounds().height));
	}
	this->background1.move(0.f, 1.f);
	this->background2.move(0.f, 1.f);
	this->window->draw(this->background1);
	this->window->draw(this->background2);
}

void Game::render()
{
	// Clear window
	this->window->clear();

	// Render world (background)
	this->renderWorld();

	// Render player
	this->player->render(this->window);

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

	
	// Display all objects
	this->window->display();
}