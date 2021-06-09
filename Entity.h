#ifndef ENTITY_H
#define ENTITY_H

#define PI 3.14159265359

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <random>

using namespace sf;
using namespace std;

class Entity
{
private:

	void initVariables();

protected:

	vector<Texture> textures;

public:

};

#endif
