# SnakeGame
This is my first experience with SFML libraries and graphic C++ programs in general. I wrote this Snake Game as an exercise to help me understand the prosses. I will be grateful for any criticism and suggestions. 


### SetUp on Linux (Ubuntu) system
1. open the terminal
2. update the Ubuntu package lists 
```
$sudo apt update && sudo apt dist-upgrade
```
3. install the GNU compiler tools (gcc/g++) and the GDB debugger
```
$ sudo apt install build-essential gdb
```
4. now install git
```
$ sudo apt install git
```
5. install SFML libraries
```
$ sudo install libsfml-dev
```
6. clone the repository
```
$ git clone https://github.com/Ekaterina-Miller/SnakeGame.git SnakeGame
```
7. got to the SnakeGame directory
```
$ cd SnakeGame
```
8. compile the project
```
$ g++ -std=C++11 *.cpp -o SnakeGame -lsfml-graphics -lsfml-window -lsfml-system
```
9. run the game
```
$ ./SnakeGame
```


## Game description
The Game lets the user enter the player’s name. After entering the name, press Enter for the Game to start
![Enter Name](assets/snake_game_name.jpg)
The goal of the Game is to eat apples (red circles) and grow the snake. The player can change the direction of the snake with a click of the mouse: one click, one direction change (up, down, left, right). This snake is not very smart. If you click behind the snake, it will try to eat itself, and … Game Over. If shake hits the border – Game Over. If a snake bites its tail, you guess it, – Game over.
![Game](assets/snake_game_game.jpg)
The Game keeps track of the top 10 scores. At the end of the Game, the user has the option to play again (with the same name) or quit the game.
![Score](assets/snake_game_score.jpg)
Enjoy!
##TODO
Right now, if the user resizes the window, the mouse clicks will not be detected correctly. I plan to fix it in the future.
