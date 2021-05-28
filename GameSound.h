#ifndef GAMESOUND_H
#define GAMESOUND_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>

using namespace sf;
using namespace std;

class GameSound
{
private:

	Music backgroundMusic;

	SoundBuffer bufferShotSound;
	SoundBuffer bufferEnemySound;
	SoundBuffer bufferPlayerSound;

	Sound bulletShotSound;
	Sound killEnemySound;
	Sound killPlayerSound;

public:

	GameSound();
	virtual ~GameSound();

	void playSound(string type, float volume);
	void pauseSound(string type);

	void playMusic(string type, float volume);
	void pauseMusic(string type);
	
};

#endif