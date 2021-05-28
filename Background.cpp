#include "Background.h"

Background::Background()
{
	if (!this->backbround1Texture.loadFromFile("Textures/backGround1texture.png"))
	{
		cout << "LOAD BACKGROUND1 TEXTURE FAILED" << endl;
	}
	if (!this->backbround2Texture.loadFromFile("Textures/backGround2texture.png"))
	{
		cout << "LOAD BACKGROUND2 TEXTURE FAILED" << endl;
	}

	this->background1.setTexture(&this->backbround1Texture);
	this->background1.setSize(Vector2f(1280, 720));
	this->background1.setPosition(0.f, 0.f);

	this->background2.setTexture(&this->backbround2Texture);
	this->background2.setSize(Vector2f(1280, 720));
	this->background2.setPosition(0.f, -(this->background2.getGlobalBounds().height));

}

Background::~Background()
{
}

void Background::update(RenderTarget* target, const float& dt)
{
	if (this->background1.getPosition().y == this->background2.getGlobalBounds().height)
	{
		this->background1.setPosition(0.f, -(this->background1.getGlobalBounds().height));
	}
	if (this->background2.getPosition().y == this->background1.getGlobalBounds().height)
	{
		this->background2.setPosition(0.f, -(this->background2.getGlobalBounds().height));
	}
	this->background1.move(0.f, 1.f);
	this->background2.move(0.f, 1.f);
}

void Background::render(RenderTarget* target)
{
	target->draw(this->background1);
	target->draw(this->background2);
}