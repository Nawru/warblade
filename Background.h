#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>

using namespace sf;
using namespace std;


class Background
{
private:

	RectangleShape background1;
	RectangleShape background2;

	Texture backbround1Texture;
	Texture backbround2Texture;

public:

	Background();
	virtual ~Background();

	void update(RenderTarget* target, const float& dt);
	void render(RenderTarget* target);

};

#endif