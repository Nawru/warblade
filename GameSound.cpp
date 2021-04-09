#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "GameSound.h"

#include <string>
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;
using namespace sf;


GameSound::GameSound()
{
	if (!this->backgroundMusic.openFromFile("Sounds\\backgroundMusic.ogg"))
	{
		cout << "LOAD MUSIC FROM FILE ERROR" << endl;
	}


	if (!this->bufferShotSound.loadFromFile("Sounds\\bulletShotSound.wav"))
	{
		cout << "LOAD BULLET SOUND FROM FILE ERROR" << endl;
	}

	this->bulletShotSound.setBuffer(this->bufferShotSound);


	if (!this->bufferEnemySound.loadFromFile("Sounds\\killEnemySound.wav"))
	{
		cout << "LOAD KILL ENEMY SOUND FROM FILE ERROR" << endl;
	}

	this->killEnemySound.setBuffer(this->bufferEnemySound);
}

GameSound::~GameSound()
{

}

void GameSound::playSound(string type, float volume)
{
	if (type == "bulletShot")
	{
		this->bulletShotSound.setVolume(volume);
		this->bulletShotSound.play();
	}
	if (type == "killEnemy")
	{
		this->killEnemySound.setVolume(volume);
		this->killEnemySound.play();
	}
}

void GameSound::pauseSound(string type)
{
	if (type == "bulletShot")
	{
		this->bulletShotSound.pause();
	}
	if (type == "killEnemy")
	{
		this->killEnemySound.pause();
	}
}

void GameSound::playMusic(string type, float volume)
{
	if (type == "backgroundMusic")
	{
		this->backgroundMusic.play();
		this->backgroundMusic.setVolume(volume);
		this->backgroundMusic.setLoop(true);
	}
}

void GameSound::pauseMusic(string type)
{
	this->backgroundMusic.pause();
}
