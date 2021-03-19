#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

using namespace sf;
using namespace std;

Game::Game()
{

	// Konstruktor wykonuje metody initVariables do wczytania ustawień ekranu i initWindow do stworzenia ekranu

	this->initVariables();
	this->initWindow();
	this->initPlayer();
	this->initEnemy();


}

Game::~Game()
{

	// Destruktor usuwa ekran

	delete this->window;
	delete this->player;
	for (auto* i : this->bullets)
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
	
	this->window = new RenderWindow(this->videoMode, "Warblade project", Style::Titlebar | Style::Close);

	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);

}

void Game::initPlayer()
{
	this->player = new Player();
	this->player->setPosition(this->window);
}

void Game::initBullet()
{

	this->bullets.push_back(
		new Bullet(
			/* Srodkowa pozycja gracza x	*/	this->player->getPlayerPos().x + (this->player->getPlayerBounds().width / 2.f),
			/* Gorna pozycja gracza y		*/	this->player->getPlayerPos().y,
			/* Kierunek lotu x				*/	0.f,
			/* Kierunek lotu Y			    */	-1.f,
			/* Typ pocisku				    */	1
		)
	);
}

void Game::initEnemy()
{
	// TODO
}


void Game::updatePlayer()
{
	this->player->update();
}



void Game::updateEnemies()
{
	// TODO
}


void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();
		//Bullet culling (top of screen)
		
		if (bullet->getBulletPos().y  < (-bullet->getBulletBounds().height))
		{
			//Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
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

	if (Keyboard::isKeyPressed(Keyboard::LControl))
	{
		if (this->player->canAttack())
		{
			this->initBullet();
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

}

void Game::render()
{
	// Clear window
	this->window->clear();

	// Render player
	this->player->render(this->window);

	// Render enemies
	// TODO

	// Render bullets
	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	// Display all objects
	this->window->display();
}