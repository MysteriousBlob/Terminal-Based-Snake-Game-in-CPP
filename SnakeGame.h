#ifndef __SNAKEGAME_H__
#define __SNAKEGAME_H__
#include <iostream> // Used for I/O interface
#include <conio.h> // Used for getch function

class SnakeGame 
{ // Game class
private: // Privately nested structs, enums, and constexpr variables
    struct Vector2 { // Used to store x and y position
        int x, y;
        bool operator==(const Vector2 &vec2){
            return x == vec2.x && y == vec2.y;
        }
    };

    const constexpr static Vector2 _dimensions {10, 10}; // Convinient definition of the dimensions

    enum class Direction{Still = 0, Left, Up, Down, Right, Unkown}; // Direction of movement

    struct Snake { // Snake object stores snake's direction of movement, it's size, and it's shape
        Vector2 tail[_dimensions.x * _dimensions.y - 1];
        int tailSize;
        Vector2 head;
        Vector2 oldHead;
        Direction direction;
    };

    struct Fruit { // Fruit class stores Vector2 position and a method which pseudo-randomly generates the new position
        Vector2 fruitPos;
        void newFruitPos() {
            fruitPos.x = std::rand() % _dimensions.x;
            fruitPos.y = std::rand() % _dimensions.y;
        }
    };

private: // Private Method
    void catchUp();
public: // Methods/Constructor/Destructor
    SnakeGame();
    ~SnakeGame() = default;

    std::ostream &draw(std::ostream &os = std::cout) const;
    friend std::ostream &operator<<(std::ostream &os, const SnakeGame &SG); // draw operator

    void logic();
    void operator()(); // logic operator

    void input(); 
    void operator()(char); // input operator
public: //Attributes
    const constexpr static Vector2 &dimensions {_dimensions}; // dimensions of the game
    bool gameOver;
    bool gameWon;
    Snake snake;
    Fruit fruit;
};

#endif