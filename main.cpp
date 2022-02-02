#include "SnakeGame.h"
#include <thread> // Used to accept the input as the snake moves

/*
    This was made by "Mysterious Blob" for entertainment purposes
    In December 20, 2021
    The headers used are <windows.h>/<iostream> for O interface and <conio.h> for I interface (I/O)
    Chrono header is also used to generate new seed every launch and move
    Inspiration for this C++ project was:
        https://github.com/NevilleBulmer/Terminal-Based-Snake-Game-In-CPP
    I hope that I commented on it well and that it's at least 'ok'
    That was my first public project, thank you for taking a look, and good luck!
*/

using namespace std::chrono;

int main() {
    srand(steady_clock::now().time_since_epoch().count()); // Set a new seed based on the system's clock
    SnakeGame game;

    std::thread update // Initiate a thread that updates the screen and processes stuff
    {
        [&] () { // Lambda
            HANDLE console = GetStdHandle((DWORD)-11); //Get console handle

            auto old = duration_cast<milliseconds>(steady_clock::now().time_since_epoch()); // Old time
            bool firstTime = true;
            while(!game.gameOver && !game.gameWon)
            {
                if(auto cur = duration_cast<milliseconds>(steady_clock::now().time_since_epoch()); cur.count() - old.count() >= game.interval.count() || firstTime)
                { // Update after a specific interval or if it's the first launch
                    game(); // Call the logic method
                    game.draw(console); // Call the draw method

                    old = cur; // Reset the old timestamp
                    firstTime = false; // Specify it's no longer the first loop
                }
            }
        }
    };

    bool pending = true;
    while(!game.gameOver && !game.gameWon)
    {
        game(char()); // Get input
        if(game.gameOver || game.gameWon)
            pending = false;
    }

    update.join(); // Wait for the last update

    if(pending)
        getch();

    system("cls"); // Resets the terminal
    return 0;
}