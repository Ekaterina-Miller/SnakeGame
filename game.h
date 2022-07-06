#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>//for cmath
#include <cmath>//for abs
#include <stdlib.h> //random
#include <time.h>    //time used as a seed for random
#include <string>
#include <fstream>
#include <sstream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

struct nameScore
{
    //int position;
    std::string name;
    int score;
};

class Game
{
public:
    Game();
    //~Game();

    //void run();
    void handleInput();
    void update();
    void render();
    bool isDone();
    bool gameOver();
    void drawBoard();
    void drawSnake();
    void drawApple();
    bool isOpen();
private:
    sf::RenderWindow mWindow;
    std::vector<sf::RectangleShape> mSnake;
    sf::CircleShape mApple;
    sf::Font font;
    sf::Text text;
    sf::Text name;
    sf::Text score;
    std::string mName;
    int mScore;
    sf::RectangleShape mBar;
    bool mIsDone;
    bool mGameBegin;
    sf::Vector2i mIncrement;
    sf::RectangleShape buttom;
    sf::VertexArray grid;//(sf::Lines, 2*(numLines));

    void handleInputDuringGame();
    void handleInputBeforeGame();
    sf::Vector2f moveSnake();
    sf::Vector2i generatePositio();
    bool isEaten();
    bool isBitten();
    bool isBump();
    int color;
    bool saveScore();
    bool isNumber(const std::string& s);
    void resetGame();
    void creatBoard();
   
};

#endif