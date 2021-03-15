#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;
using namespace std;

class Game
{
private:

	//Variables and window
	RenderWindow* window;
	VideoMode videoMode;
	Event ev;
	
	Sprite player;
	Texture playerTexture;


	void initVariables();
	void initWindow();
	void initPlayer();


	void updatePlayerPosition(int vector);


	void renderPlayer();

public:

	Game(); //Constructor
	virtual ~Game(); //Destructor

	const bool running() const; //Check window running (true or false)

	// Functions
	void pollEvents();
	void update();
	void render();
};