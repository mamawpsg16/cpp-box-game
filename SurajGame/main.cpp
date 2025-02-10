#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
    /* INITIALIZE RANDOM NUMBER */
    srand(static_cast<unsigned>(time(NULL)));

    Game game;

    while (game.isRunning() && !game.isEndGame())
    {
       
        game.update();

        game.render();
    }
}