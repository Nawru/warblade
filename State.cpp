#include "State.h"

State::State(RenderWindow* window)
{
	this->window = window;
	this->quit = false;
}

State::~State()
{
}

const bool& State::getQuit() const
{
	return this->quit;
}

const bool& State::getNext() const
{
	return this->next;
}

void State::checkForQuit()
{
	if (Keyboard::isKeyPressed((Keyboard::Escape)))
		this->quit = true;
}

void State::updateMousePosition()
{
	this->MousePosScreen = Mouse::getPosition();
	this->MousePosWindow = Mouse::getPosition(*this->window);
	this->MousePosView = this->window->mapPixelToCoords(Mouse::getPosition(*this->window));
}

void State::updateInput(RenderTarget* target, const float& dt)
{
	this->checkForQuit();
}