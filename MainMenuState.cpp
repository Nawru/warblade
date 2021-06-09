#include "MainMenuState.h"

MainMenuState::MainMenuState(RenderWindow* window)
	: State(window)
{

	this->initObjects();
	this->window->setMouseCursorVisible(true);

}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::checkForQuit()
{
	if (Keyboard::isKeyPressed((Keyboard::Escape)))
		this->quit = true;
}

void MainMenuState::endState()
{
	cout << "End mainMenu state" << endl;
}

void MainMenuState::initObjects()
{
	if (!this->startGameButtonTexture.loadFromFile("Textures/MainMenu/StartGameButton.png"))
	{
		cout << "LOAD MAINMENU STARTGAMEBUTTON TEXTURE FAILED" << endl;
	}
	this->startGameButton.setTexture(&this->startGameButtonTexture);
	this->startGameButton.setSize(Vector2f(400, 400));
	this->startGameButton.setPosition(Vector2f(440, 300));

	if (!this->backgroundTexture.loadFromFile("Textures/MainMenu/Background.jpg"))
	{
		cout << "LOAD MAINMENU BACKGROUND1 TEXTURE FAILED" << endl;
	}
	this->background.setTexture(&this->backgroundTexture);
	this->background.setSize(Vector2f(1280, 720));
	this->background.setPosition(Vector2f(0, 0));

	if (!font.loadFromFile("Fonts\\No Virus.ttf"))
	{
		cout << "FAILED GUI FONTS LOAD!" << endl;
	}

}

void MainMenuState::updateInput(RenderTarget* target, const float& dt)
{
	this->checkForQuit();
}

const bool& MainMenuState::getQuit() const
{
	return this->quit;
}

const bool& MainMenuState::getNext() const
{
	return this->next;
}

void MainMenuState::updateButtonClick()
{
	if (this->MousePosWindow.x >= this->startGameButton.getPosition().x 
		&& this->MousePosWindow.x <= this->startGameButton.getPosition().x + this->startGameButton.getGlobalBounds().width
		&& this->MousePosWindow.y >= this->startGameButton.getPosition().y
		&& this->MousePosWindow.y <= this->startGameButton.getPosition().y + this->startGameButton.getGlobalBounds().height)
	{
		this->startGameButton.setFillColor(Color::Green);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			this->next = true;
		}
	}
	else
	{
		this->startGameButton.setFillColor(Color::White);
	}
}

void MainMenuState::update(RenderTarget* target, const float& dt)
{
	this->updateButtonClick();
	this->updateMousePosition();
	this->updateInput(target, dt);
}

void MainMenuState::render(RenderTarget* target)
{
	target->draw(this->background);
	target->draw(this->startGameButton);
}