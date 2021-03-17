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

	//Variables and window
	RenderWindow* window;
	VideoMode videoMode;
	Event event;
	Player player;
	

	void initVariables();
	void initWindow();


public:

	Game(); //Constructor
	virtual ~Game(); //Destructor

	const bool running() const; //Check window running (true or false)

	// Functions
	void pollEvents();
	void update();
	void render();
};