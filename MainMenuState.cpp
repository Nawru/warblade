#include "MainMenuState.h"

MainMenuState::MainMenuState(RenderWindow* window)
	: State(window)
{
	if (!font.loadFromFile("Fonts\\No Virus.ttf"))
	{
		cout << "FAILED GUI FONTS LOAD!" << endl;
	}
	this->startGameButton.setSize(Vector2f(100, 100));
	this->startGameButton.setPosition(Vector2f(0, 0));

	this->pressSpaceToStartGame.setFont(font);
	this->pressSpaceToStartGame.setString("PRESS SPACE TO START GAME");
	this->pressSpaceToStartGame.setCharacterSize(100);
	this->pressSpaceToStartGame.setFillColor(Color::Red);
	this->pressSpaceToStartGame.setPosition(Vector2f(50, 200));
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::checkForQuit()
{
	if (Keyboard::isKeyPressed((Keyboard::Space)))
		this->quit = true;
}

void MainMenuState::endState()
{
	cout << "End mainMenu state" << endl;
}

void MainMenuState::updateInput(RenderTarget* target, const float& dt)
{
	this->checkForQuit();
}

void MainMenuState::updateButtonClick()
{
	cout << MousePosScreen.x << MousePosScreen.y << endl;
}

void MainMenuState::update(RenderTarget* target, const float& dt)
{
	this->updateButtonClick();
	this->updateMousePosition();
	this->updateInput(target, dt);
}

void MainMenuState::render(RenderTarget* target)
{
	target->draw(this->pressSpaceToStartGame);
	target->draw(this->startGameButton);
}