#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "State.h"

class MainMenuState :
    public State
{
private:

	RectangleShape startGameButton;

	Font font;
	Text pressSpaceToStartGame;

	void updateInput(RenderTarget* target, const float& dt);
	void updateButtonClick();

public:

    MainMenuState(RenderWindow* window);
    virtual ~MainMenuState();

	void checkForQuit();

	void endState();

	void update(RenderTarget* target, const float& dt);
	void render(RenderTarget* target);
};

#endif