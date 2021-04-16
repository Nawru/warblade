#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <string>
#include "Game.h"

using namespace sf;
using namespace std;

class Items
{

private:

	Sprite moneyItem50;
	Sprite moneyItem100;
	Sprite moneyItem200;
	Sprite moneyItem500;

	Sprite addSpeedItem;
	Sprite removeSpeedItem;
	Sprite addBulletItem;
	Sprite removeBulletItem;

	Texture moneyItem50Texture;
	Texture moneyItem100Texture;
	Texture moneyItem200Texture;
	Texture moneyItem500Texture;
	Texture addSpeedItemTexture;
	Texture removeSpeedItemTexture;
	Texture addBulletItemTexture;
	Texture removeBulletItemTexture;

	void initMoneyItem(int type);

	void initAddSpeedItem();
	void initRemoveSpeedItem();

	void initAddBulletItem();
	void initRemoveBulletItem();

public:

	Items(float pos_x, float pos_y, string type);
	~Items();

	void itemsUpdate();
	void itemsRender(RenderTarget* target);
};

