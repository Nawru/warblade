#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <sstream>

using namespace sf;
using namespace std;

class Gui
{
private:

	RectangleShape backHPbar;
	RectangleShape HPbar;

	RectangleShape backBULLETbar;
	RectangleShape BULLETbar;

	RectangleShape backSPEEDbar;
	RectangleShape SPEEDbar;

	Font font;

	stringstream ss;

	Text level;
	Text points;
	Text money;

	Text gameOverText;

	bool gameOver = false;

public:

	void setGUIhp(int hp);
	void setGUIspeed(int speed);
	void setGUIbullet(int bullet);
	void setGUIlevel(int level);
	void setGUIpoints(int points);
	void setGUImoney(int money);
	void renderGameOver();

	void reder(RenderTarget* target);

	Gui();
	~Gui();

};

#endif