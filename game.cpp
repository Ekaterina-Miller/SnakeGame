#include "game.h"

/**
 * @brief Construct a new Game:: Game object
 *          
 */
Game::Game() : mWindow(sf::VideoMode(500, 700), "Snake Game") //, mSnake(sf::Quads, 2)
{
    
    mName = "";
    color=1;//white -1 black

    if (!font.loadFromFile("college.ttf"))
    {
        std::cout<<"Erro opening file\n";
    }
    //creat a blinking bar
    mBar.setSize(sf::Vector2f(20, 5));
    mBar.setPosition(200,80);
    mBar.setFillColor(sf::Color::White);

    creatBoard();

    resetGame();

    //apple
    mApple.setRadius(11.5);
    mApple.setFillColor(sf::Color::Red);
    //generate the positio
    srand(time(NULL));
    sf::Vector2i applePosition=generatePositio(); 
    mApple.setPosition(applePosition.x, applePosition.y);

    mGameBegin=false;
    mIsDone = false;
}


/**
 * @brief This function creats the game board
 * 
 */
void Game::creatBoard()
{
    // select the font
    text.setFont(font); // font is a sf::Font
    text.setString("Name: \nScore:");
    text.setLineSpacing(2);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(45); // in pixels, not points!
    text.setPosition(30,29);

    name.setFont(font); // font is a sf::Font
    name.setFillColor(sf::Color::Red);
    name.setCharacterSize(45); // in pixels, not points!
    name.setPosition(200,29);


    score.setFont(font);
    score.setFillColor(sf::Color::Red);
    score.setCharacterSize(45); // in pixels, not points!
    score.setPosition(200,120);
    
    
    buttom.setSize(sf::Vector2f(450, 450));
    buttom.setPosition(sf::Vector2f(25.f, 225.f));
    buttom.setFillColor(sf::Color::Green);
    buttom.setOutlineThickness(25);
    buttom.setOutlineColor(sf::Color::Yellow);



    // initialize values
    int rows = 450/25, cols=450/25;
    int numLines = rows+cols+2;
    grid.setPrimitiveType(sf::Lines);
    grid.resize(2*(numLines));
    

    float rowH = 25;
    float colW = 25;
    float rowY=225;
    // row separators
    for(int i=0; i < rows; i++){
        grid[i*2].position = sf::Vector2f(25, rowY);
        grid[i*2+1].position = sf::Vector2f(475, rowY);
        rowY+=25;

    }
    // column separators
    float colX=25;
    for(int i=rows; i < numLines; i++){
        grid[i*2].position = sf::Vector2f(colX, 225);
        grid[i*2+1].position = sf::Vector2f(colX, 675);
        colX+=25;
    }
}

/**
 * @brief This function returns all game variables to their initial state.
 * 
 */
void Game::resetGame()
{
    mSnake.clear(); //empty the snake vector
    mScore = 0;     //reset score
    mIncrement = sf::Vector2i(0, 0); //snake does not move
    sf::RectangleShape rectangle(sf::Vector2f(23, 23));
    //Creat a snake size 3
    mSnake.push_back(rectangle);
    mSnake.push_back(rectangle);
    mSnake.push_back(rectangle);
    mSnake[0].setPosition(sf::Vector2f(226,426));
    mSnake[0].setFillColor(sf::Color::Magenta);
    mSnake[1].setPosition(sf::Vector2f(226,451));
    mSnake[1].setFillColor(sf::Color::Blue);
    mSnake[2].setPosition(sf::Vector2f(226,476));
    mSnake[2].setFillColor(sf::Color::Blue);
}

/**
 * @brief This function generates the position for the apple. 
 *          It checks that the apple is not on the snake.
 * 
 * @return sf::Vector2i - position
 */
sf::Vector2i Game::generatePositio()
{
    sf::Vector2i applePosition;
    bool goodPosition = false;
    while(!goodPosition)
    {
        goodPosition = true;
        applePosition.x = 26 + (rand()%18)*25;
        applePosition.y = 226 + (rand()%18)*25;

        //check that it is not on the snake
        for (unsigned int i = 0; i < mSnake.size(); i++)
        {
            if (int(mSnake[i].getPosition().x) == applePosition.x && 
                int(mSnake[i].getPosition().y) == applePosition.y)
            {
                goodPosition = false;
                break;
            }
        }
    } 
    return applePosition;
}

/**
 * @brief This function decides which input handle function to call.
 * 
 */
void Game::handleInput()
{
    if (mGameBegin)
    {
        handleInputDuringGame();
    }
    else{
        handleInputBeforeGame();
    }
}

/**
 * @brief This function handles user input(name entering) before the game starts.
 * 
 */
void Game::handleInputBeforeGame()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            // Close window button clicked.
            mWindow.close();
        }
        //checks if user press any key
        if(event.type==sf::Event::TextEntered)
        {
            //if leter is enterd
            if (event.text.unicode < 128)
            {
                //if user press enter or name size longer then 12
                if (event.text.unicode==13 || mName.size()==13)
                {
                   mGameBegin=true; //start the game
                   color=-1;//set cursor color to black - don't display during the game 
                }
                else
                {
                    //add it to the name
                    mName.push_back(static_cast<char>(event.text.unicode));

                }
            } 
        }
    }   
}

/**
 * @brief This function handles user input during the game. 
 *          It determines the Snake's direction based on the mouse click's position.
 * 
 */
void Game::handleInputDuringGame()
{
    sf::Event event;
    sf::Vector2f click;
    sf::Vector2f difference;
    //get midle of the head
    sf::Vector2f adjustment;

    //find snake direction
    if (mSnake[0].getPosition().x==mSnake[1].getPosition().x &&
        mSnake[0].getPosition().y < mSnake[1].getPosition().y){
        //skane is going up
        adjustment.x=11.5;
        adjustment.y=0;
    }
    else if (mSnake[0].getPosition().x==mSnake[1].getPosition().x &&
        mSnake[0].getPosition().y > mSnake[1].getPosition().y){
        //skane is going down
        adjustment.x=11.5;
        adjustment.y=23;
    }
    else if (mSnake[0].getPosition().y==mSnake[1].getPosition().y &&
        mSnake[0].getPosition().x < mSnake[1].getPosition().x){
        //skane is going left
        adjustment.x=0;
        adjustment.y=11.5;
    }
    else if (mSnake[0].getPosition().y==mSnake[1].getPosition().y &&
        mSnake[0].getPosition().x > mSnake[1].getPosition().x){
        //skane is going right
        adjustment.x=23;
        adjustment.y=11.5;
    }

    while(mWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            // Close window button clicked.
            mWindow.close();
        }

        if(event.type==sf::Event::MouseButtonPressed)
        {
            if(event.mouseButton.button==sf::Mouse::Left)
            {
                //get position of the click
                click.x = event.mouseButton.x;
                click.y = event.mouseButton.y;

                //get absolut difrense between head and click
                difference.x=std::abs(mSnake[0].getPosition().x+adjustment.x-click.x);
                difference.y=std::abs(mSnake[0].getPosition().y+adjustment.y-click.y);
                //horisontal difrence is more
                if (difference.x>difference.y)
                {
                    //click on the left
                    if (mSnake[0].getPosition().x+adjustment.x-click.x>0)
                    {
                        mIncrement.x = -25;
                        mIncrement.y = 0;
                    }
                    else{//click on the right
                        mIncrement.x = 25;
                        mIncrement.y = 0;
                    }
                }
                else //vertical difrence is more
                {
                    //click up
                    if (mSnake[0].getPosition().y+adjustment.x-click.y>0)
                    {
                        mIncrement.x = 0;
                        mIncrement.y = -25;
                    }
                    else{//click down
                        mIncrement.x = 0;
                        mIncrement.y = 25;
                    }
                }
            }
        }
    }
}

/**
 * @brief This function moves the cursor (before the game starts) 
 *         and updates the snake or determines if the conditions 
 *         to end the game are met (during the game). 
 * 
 */
void Game::update()
{
    if (mGameBegin)
    {
        const sf::Vector2f talePosition = moveSnake();
        if (isEaten())
        {
            sf::Vector2i applePosition=generatePositio(); 
            mApple.setPosition(applePosition.x, applePosition.y);
            //increase the linth of the snake
            sf::RectangleShape rectangle(sf::Vector2f(23, 23));
            mSnake.push_back(rectangle);
            mSnake[mSnake.size()-1].setPosition(talePosition);
            mSnake[mSnake.size()-1].setFillColor(sf::Color::Blue);
            //update the score
            mScore++;
        }
        if (isBitten())
        {
            mIsDone = true;
        }
        if (isBump())
        {
            mIsDone = true;
        }

        score.setString(std::to_string(mScore));
    }

    else
    {
        name.setString(mName);
        mBar.setPosition(200+ mName.size()*22.5,80 );
        if (color==1)
        {
            mBar.setFillColor(sf::Color::White);
            color*=-1;
        }else{
            mBar.setFillColor(sf::Color::Black);
            color*=-1;
        }

    }
}

/**
 * @brief This function moves the snake head according to mIncrement and
 *         moves each body piece to the position of the previous piece
 * 
 * @return sf::Vector2f previouse position of the tail(last piece)
 */
sf::Vector2f Game::moveSnake()
{
   const sf::Vector2f talePosition = mSnake[mSnake.size()-1].getPosition();
   if (mIncrement.x != 0 || mIncrement.y != 0)
   {
       for (unsigned int i =mSnake.size()-1; i>0; --i)
        {
            mSnake[i].setPosition(mSnake[i-1].getPosition());
        }
        mSnake[0].setPosition(mSnake[0].getPosition().x+mIncrement.x, mSnake[0].getPosition().y+mIncrement.y);
   }
   return talePosition;
}

/**
 * @brief This function checks if snake eats the apple
 * 
 * @return true 
 * @return false 
 */
bool Game::isEaten()
{
    if (mSnake[0].getPosition() == mApple.getPosition())
    {
        return true;
    }
    return false;
}

/**
 * @brief This function checks if the snake bites itself.
 * 
 * @return true 
 * @return false 
 */
bool Game::isBitten()
{
    for (unsigned int i = 1; i < mSnake.size(); i++)
        {
            if (mSnake[0].getPosition() == mSnake[i].getPosition())
            {
                return true;
            }
        }
    return false;
}

/**
 * @brief This function checks if the snake bumps into the barrier.
 * 
 * @return true 
 * @return false 
 */
bool Game::isBump()
{
    if (mSnake[0].getPosition().x < 25 || mSnake[0].getPosition().x > 475
        || mSnake[0].getPosition().y < 225 || mSnake[0].getPosition().y > 675)
    {
        return true;
    }
    return false;
}

/**
 * @brief This function draw the game board
 * 
 */
void Game::drawBoard(){
    
    // draw it
    mWindow.draw(buttom);
    mWindow.draw(grid);
    mWindow.draw(text);
    mWindow.draw(name);
    mWindow.draw(mBar);
    mWindow.draw(score);
}

/**
 * @brief This function draw the snake
 * 
 */
void Game::drawSnake()
{
    unsigned int size = mSnake.size();
    for (unsigned int i = 0; i<size; i++)
    {
        mWindow.draw(mSnake[i]);
    }

}

/**
 * @brief This function draw the apple
 * 
 */
void Game::drawApple()
{
    mWindow.draw(mApple);
}


/**
 * @brief This function displays the current state of the game.
 * 
 */
void Game::render()
{
    mWindow.clear();
    drawBoard();
    if (mGameBegin)
    {
        drawSnake();
        drawApple();
        mWindow.draw(mBar);
    }
    else
    {
        mWindow.draw(mBar);
    }
    mWindow.display();
}


/**
 * @brief Checks if game is done
 * 
 * @return true 
 * @return false 
 */
bool Game::isDone()
{
    return (mIsDone);
}

/**
 * @brief This function updates the score file if needed
 * 
 * @return true 
 * @return false 
 */
bool Game::saveScore()
{
    std::string line;
    nameScore person;
    nameScore winners[10];
    std::ifstream scoreFile("bestScores.txt");
    if (!scoreFile)
    {
        return false;
    }
    else
    { //read file into the array
        std::getline(scoreFile,line); //skip firest line
        int numberOfNames = 0;
        while(std::getline(scoreFile,line) && numberOfNames<=10)
        {
            std::size_t space1 = line.find(" ");      // position of "live" in str
            std::size_t space2 = (line.substr(space1+1)).find(" ")+space1 +1;
            person.name=line.substr(space1+1,space2-space1-1);
            std::string str_score=line.substr(space2+1);
            if (str_score!="")//isNumber(str_score))
            {
                person.score=std::stoi(str_score); 
                winners[numberOfNames]=person;
                numberOfNames++;
            } else
            {
                numberOfNames++;
                break;
            }
        }
        numberOfNames--;//point i to the last valid element in array
        scoreFile.close();

        //compare new score
        if (numberOfNames<=9 || mScore > winners[numberOfNames].score)
        {
            //find the correct position
            for (int j = numberOfNames; j > 0; j--)
            {
                if (mScore > winners[j].score)
                {
                    if (j<=9)
                    {
                        winners[j+1].score=winners[j].score;
                        winners[j+1].name=winners[j].name;
                    }
                    
                }
                else
                {
                    winners[j+1].score=mScore;
                    winners[j+1].name=mName;
                    numberOfNames++;
                    break;
                }
            }
        }

        //write back to the file
        std::ofstream scoreFile("bestScores.txt");
        scoreFile<<"   Top 10\n";
        for (int j = 0; j < numberOfNames; j++)
        {
            scoreFile<<j+1<<". "<< winners[j].name<<" "<< winners[j].score<<"\n";
        }
        scoreFile.close();
    }
    return true;
}

/**
 * @brief This function creates and displays the Game Over window. 
 *         It asks the users if they want to play again.
 * 
 * @return true 
 * @return false 
 */
bool Game::gameOver()
{
    //save the score
    saveScore();

    sf::RectangleShape gameOver(sf::Vector2f(400, 400));
    gameOver.setPosition(sf::Vector2f(50.f, 200.f));
    gameOver.setFillColor(sf::Color::Blue);
    gameOver.setOutlineThickness(5);
    gameOver.setOutlineColor(sf::Color::Yellow);

    sf::Text over;
    over.setFont(font); // font is a sf::Font
    over.setString("GAME OVER");
    over.setFillColor(sf::Color::White);
    over.setCharacterSize(45); // in pixels, not points!
    over.setPosition(138,210);


    std::ifstream scoreFile("bestScores.txt");
    std::stringstream stream;
    stream<<scoreFile.rdbuf();
    sf::Text winners(stream.str(),font,20);
    winners.setPosition(150,260);
    scoreFile.close();

    sf::Text playAgain;
    playAgain.setFont(font); // font is a sf::Font
    playAgain.setString("Do you want to play again?");
    playAgain.setFillColor(sf::Color::White);
    playAgain.setCharacterSize(30); // in pixels, not points!
    playAgain.setPosition(60,500);

    sf::Text yes;
    yes.setFont(font); // font is a sf::Font
    yes.setString("YES");
    yes.setFillColor(sf::Color::White);
    yes.setCharacterSize(30); // in pixels, not points!
    yes.setPosition(138,550);

    sf::Text no;
    no.setFont(font); // font is a sf::Font
    no.setString("NO");
    no.setFillColor(sf::Color::White);
    no.setCharacterSize(30); // in pixels, not points!
    no.setPosition(320,550);


    while (mWindow.isOpen())
    {
        sf::Event event;
        while (mWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mWindow.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
        
                    //if user click "yes"
                    if (event.mouseButton.x>138 && event.mouseButton.x < 186 &&
                        event.mouseButton.y>560 && event.mouseButton.y < 580 )
                    {
                        //yes.setFillColor(sf::Color::Red);
                        //reset score
                        resetGame();
                        mGameBegin=true;
                        mIsDone = false;
                        color=-1;
                        mWindow.clear();
                        return true;
                    }
                    //if user click "no"
                    if (event.mouseButton.x>322 && event.mouseButton.x < 351 &&
                        event.mouseButton.y>560 && event.mouseButton.y < 580 )
                    {
                        //no.setFillColor(sf::Color::Red);
                        return false;
                    }
                    
                }
                
            }

        }
        mWindow.draw(gameOver);
        mWindow.draw(over);
        mWindow.draw(winners);
        mWindow.draw(playAgain);
        mWindow.draw(yes);
        mWindow.draw(no);
        mWindow.display();
    }
    return false;
}

bool Game::isOpen()
{
    return mWindow.isOpen();
}