#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include "State.h"
#include "GameState.h"
#include "MainMenuState.h"

class GameSystem
{

private:

	RenderWindow* window;
	VideoMode videoMode;
	Event event;

	Clock dtClock;
	float dt;

	stack<State*> states;

	void initWindow();
	void initStates(string type);

public:

	GameSystem();
	virtual ~GameSystem();

	void endApplication();

	void updateDt();
	void updateEvents();

	void update();
	void render();

	void run();

};

#endif