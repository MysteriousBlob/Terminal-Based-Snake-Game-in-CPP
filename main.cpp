#include "SnakeGame.h"
#include <time.h> // Used to generate a new seed

/*
    This was made by "Mysterious Blob" for entertainment purposes
    In December 20, 2021
    The headers used are <iostream> for I/O interface and <conio.h> for getch function
    Time.h header is also used to generate new seed every launch
    Inspiration for this C++ project was:
        https://github.com/NevilleBulmer/Terminal-Based-Snake-Game-In-CPP
    I hope that I commented on it well and that it's at least 'ok'
    That was my first public project, thank you for taking a look, and good luck!
*/

int main() {
    srand(time(nullptr)); // Set a new seed based on the system's clock

    system("cls");
    replay:
    SnakeGame game;
    while(!game.gameOver && !game.gameWon)
    {
        std::cout << game; // Display
        game(char()); // Get input
        game(); // Logic
    }
    std::cout << game << "\nDo you want to play again? (Y/Any key) "; // Display last time either a loss or a win
    char choice = getch(); // Get user's choice;

    if(choice == 'y' || choice == 'Y')
        goto replay;

    system("cls"); // Resets the terminal
    return 0;
}