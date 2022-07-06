#include "game.h"

int main()
{
    Game game;
    //game.run();
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 2);
    sf::Clock clock; // starts the clock
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    
    do
    {
        while(!game.isDone()&& game.isOpen())
        {
            timeSinceLastUpdate += clock.restart();
    
            game.handleInput();  
            while (timeSinceLastUpdate > TIME_PER_FRAME)
            {
                timeSinceLastUpdate -= TIME_PER_FRAME;
                game.update();
            }

            game.render();

        }
    }
    while (game.gameOver() && game.isOpen());


    return 0;
}

