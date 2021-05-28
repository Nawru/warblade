#ifndef STATE_H
#define STATE_H

#define PI 3.14159265359

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <vector>
#include <windows.h>
#include <string>
#include <cmath>
#include <cstdlib>
#include <stack>
#include <map>
#include <math.h>
#include <random>
#include <sstream>

#include "Bullet.h"
#include "Enemy.h"
#include "Items.h"
#include "Player.h"
#include "Background.h"
#include "GameSound.h"
#include "Gui.h"

using namespace sf;
using namespace std;

class State
{

private:



protected:

	bool quit;

	RenderWindow* window;
	vector<Texture> textures;

	Vector2i MousePosScreen;
	Vector2i MousePosWindow;
	Vector2f MousePosView;

public:

	State(RenderWindow* window);
	virtual ~State();

	virtual void updateMousePosition();

	virtual void checkForQuit() = 0;
	virtual void endState() = 0;

	const bool& getQuit() const;

	virtual void updateInput(RenderTarget* target, const float& dt) = 0;
	virtual void update(RenderTarget* target, const float& dt) = 0;
	virtual void render(RenderTarget* target) = 0;
};

#endif