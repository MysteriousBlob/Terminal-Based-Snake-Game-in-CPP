#include "SnakeGame.h"
/*
    This was made by "Mysterious Blob" for entertainment purposes
    In December 20, 2021
    The headers used are <iostream> for I/O interface and <conio.h> for getch function
    Inspiration for this C++ project was:
        https://github.com/NevilleBulmer/Terminal-Based-Snake-Game-In-CPP
    I hope that I commented on it well and that it's at least 'ok'
    That was my first public project, thank you for taking a look, and good luck!
*/

int main() {
    SnakeGame game;
    while(!game.gameOver && !game.gameWon)
    {
        std::cout << game; // Display
        game(char()); // Get input
        game(); // Logic
    }
    std::cout << game; // Display last time either a loss or a win
    return 0;
}