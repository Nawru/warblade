#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "State.h"

class MainMenuState :
    public State
{
private:

	RectangleShape startGameButton;
	RectangleShape background;

	Texture startGameButtonTexture;
	Texture backgroundTexture;

	Font font;

	void initObjects();

	void updateInput(RenderTarget* target, const float& dt);
	void updateButtonClick();

public:

    MainMenuState(RenderWindow* window);
    virtual ~MainMenuState();

	void checkForQuit();
	const bool& getQuit() const;
	const bool& getNext() const;

	void endState();

	void update(RenderTarget* target, const float& dt);
	void render(RenderTarget* target);
};

#endif