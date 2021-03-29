#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include "Game.h"

using namespace sf;
using namespace std;

int main()
{
    srand(time(NULL));

    Game game;

    while (game.running())
    {
        game.update();
        game.render();
    }

    return 0;
}