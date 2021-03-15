#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include "Game.h"

using namespace sf;
using namespace std;

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initPlayer();
}

Game::~Game()
{
	delete this->window;

}

void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = 720;
	this->videoMode.width = 1280;
	
	this->window = new RenderWindow(this->videoMode, "Warblade project", Style::Titlebar | Style::Close);

	this->window->setFramerateLimit(60);

}

void Game::initPlayer()
{
	if (!this->playerTexture.loadFromFile("playerTexture.png"))
	{
		cout << "LOAD PLAYER TEXTURE FAILED" << endl;
		system("pause");
	}
	this->player.setTexture(this->playerTexture);
	
	this->player.scale(0.2, 0.2);
	this->player.setPosition(580, 620);
	//this->player.setTextureRect(IntRect(0, 0, 64, 64));
}

void Game::updatePlayerPosition(int vector)
{
	switch (vector)
	{
	case 1:
		for(int i = 0; i < 10; i++)
		{
			this->player.move(-1.f, 0.f);
		}
		break;
	case 2:
		for(int i = 0; i < 10; i++)
		{
			this->player.move(1.f, 0.f);
		}
		break;
	case 3:
		for (int i = 0; i < 10; i++)
		{
			this->player.move(0.f, -1.f);
		}
		break;
	case 4:
		for (int i = 0; i < 10; i++)
		{
			this->player.move(0.f, 1.f);
		}
	}
}

void Game::renderPlayer()
{
	this->window->draw(player);
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->ev.key.code == Keyboard::Escape)
				this->window->close();
			if (this->ev.key.code == Keyboard::A)
				this->updatePlayerPosition(1);
			if (this->ev.key.code == Keyboard::D)
				this->updatePlayerPosition(2);
			if (this->ev.key.code == Keyboard::W)
				this->updatePlayerPosition(3);
			if (this->ev.key.code == Keyboard::S)
				this->updatePlayerPosition(4);
			if (this->ev.key.code == Keyboard::LControl)
				this->window->close();
			break;
		}
	}
}

void Game::update()
{
	this->pollEvents();
}

void Game::render()
{

	// Clear old frame -> render objects -> display frame in window 

	this->window->clear();

	this->renderPlayer();

	this->window->display();
}
