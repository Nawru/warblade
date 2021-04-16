#pragma once

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
#include "Gui.h"


using namespace sf;
using namespace std;


class Background
{
private:


	Sprite background1;
	Sprite background2;
	Texture backbround1Texture;
	Texture backbround2Texture;

public:

	Background();
	virtual ~Background();

	void updateBackground(RenderTarget* target);
	void renderBackground(RenderTarget* target);
};

