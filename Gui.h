#pragma once

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

class Gui
{
private:

	Sprite backgroundHPbar;
	Sprite backgroundSPEEDbar;
	Sprite backgroundBULLETbar;

	vector<Sprite> HPbar;
	vector<Sprite> SPEEDbar;
	vector<Sprite> BULLETbar;

	Text level;
	Text points;
	Text money;


public:

	void update();
	void reder(RenderTarget* target);

	Gui();
	~Gui();

};

