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
}

Game::~Game()
{

	// Destruktor usuwa ekran

	delete this->window;

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

}



const bool Game::running() const
{

	// Zwracanie true lub false w zaleznosci od tego czy okno gry jest nadal uruchomione

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

void Game::update()
{

	// Metoda ta wykonuje metode Game::pollEvent oraz odwoluje sie do klasy Player do wykonania jej metody Player::update
	// Dla utworzonego obiektu player

	this->pollEvents();
	this->player.update(this->window);
}

void Game::render()
{

	// Clear old frame -> render objects -> display frame in window 

	this->window->clear();

	this->player.render(this->window);

	this->window->display();
}
