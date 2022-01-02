#include "SnakeGame.h"
std::ostream &operator<<(std::ostream &os, const SnakeGame &SG)
{
    return SG.draw(os);
}
void SnakeGame::operator()()
{
    logic();
}
void SnakeGame::operator()(char)
{
    input();
}

SnakeGame::SnakeGame() // Constructs a SnakeGame obj
    :gameOver{}, gameWon{}, 
    //   tail, tailSize, head, oldHead, direction
    snake{{}, 0, {_dimensions.x / 2 - 1, _dimensions.y/2 - 1}, snake.head, Direction::Still} 
{
    do { // Generate the fruit on a unique position
        fruit.newFruitPos();
    } while(fruit.fruitPos == snake.head);
}

std::ostream &SnakeGame::draw(std::ostream &os) const
{
    std::system("cls"); // Clear terminal
    if(gameOver)
    {
        os << "You lost\nYour score: " << snake.tailSize << "\n\nPress any key to continue...";
        return os;
    }
    else if(gameWon)
    {
        os << "YOU WON!\nWell Played!\n\nPress any key to continue...";
        return os;
    }

/* [Sample output]
    score: 0
    # # # # # # #
    #         P #
    #           #
    #     O     # 
    #           #
    #           #
    # # # # # # #
*/

    os << "score: " << snake.tailSize << std::endl; // Score at the top

    os << "# ";  // The top line
    for (int x = 0; x < _dimensions.x; x++) {
        os << "# ";
    }
    os << "#\n";
    
    for (int y = 0; y < _dimensions.y; y++) // Loop through Y positions
    {
        os << "# "; // First line
        for (int x = 0; x < _dimensions.x; x++) // Loop through X positions
        { 
            if(snake.head.x == x && snake.head.y == y) // Output the snake's head
            {
                os << "O";
            }
            
            else if(fruit.fruitPos.x == x && fruit.fruitPos.y == y) // Output the fruit
            {
                os << "P";
            }

            else if(snake.tailSize != 0) 
            { // Removes the unnecessary allocation
                bool foundTail = false; // Check if tail was found
                for (int i = 0; i < snake.tailSize; i++) 
                { // Loop through the tails
                    if(snake.tail[i].x == x && snake.tail[i].y == y)
                    { // Output the tail
                        os << "o";
                        foundTail = true;
                        break;
                    }
                }
                if(!foundTail) // If no tail was found
                    os << " ";
            }

            else //If there's no tail yet
            {
                os << " ";
            }

            os << " "; // Spacing to make the sides even
        }
        os << "#\n"; // Second line
    }

    os << "# "; // Bottom line
    for (int x = 0; x < _dimensions.x; x++) {
        os << "# ";
    }
    os << "#\n";

    os << "Press w/a/s/d to move: "; // Moving keys hint

    return os;
}

void SnakeGame::catchUp()
{ // Makes tail catch up to the head
    for (int i = 0; i < snake.tailSize; i++) // Loop through all tails
    {
        if(i+1 == snake.tailSize) // If last tail
            snake.tail[i] = snake.head; // Equate to the head
        else
            snake.tail[i] = snake.tail[i+1]; // Equate to the next tail
    }
}

void SnakeGame::logic()
{
    switch (snake.direction)
    {
    case Direction::Left: // Move the snake left
        if(snake.head.x-1 != fruit.fruitPos.x || snake.head.y != fruit.fruitPos.y)
            catchUp(); // Catch up if no fruit found
        snake.head.x--; // Head will move one tile left
        break;
    case Direction::Up: // Move the snake up
        if(snake.head.x != fruit.fruitPos.x || snake.head.y-1 != fruit.fruitPos.y)
            catchUp(); // Catch up if no fruit found
        snake.head.y--; // Head will move one tile up
        break;
    case Direction::Down: // Move the snake down
        if(snake.head.x != fruit.fruitPos.x || snake.head.y+1 != fruit.fruitPos.y)
            catchUp(); // Catch up if no fruit found
        snake.head.y++; // Head will move one tile down
        break;
    case Direction::Right: // Move the snake right
        if(snake.head.x+1 != fruit.fruitPos.x || snake.head.y != fruit.fruitPos.y)
            catchUp(); // Catch up if no fruit found
        snake.head.x++; // Head will move one tile right
        break;
    default: // Default case to remove compiler warnings
        break;
    }

    if(snake.head.x >= _dimensions.x || snake.head.y >= _dimensions.y || snake.head.x < 0 || snake.head.y < 0) // If head outside the board
        gameOver = true; //Lose
    for (int i = 0; i < snake.tailSize && !gameOver; i++)
    { //Check if head of the snail and it's tail are intersecting
        if(snake.tail[i] == snake.head)
        {
            gameOver = true; // Lose
            break;
        }
    }

    if(snake.head == fruit.fruitPos)
    { // Gain score and new tail
        // Fill in the gap from not catching up
        snake.tail[snake.tailSize] = snake.oldHead; 
        snake.tailSize++; // Allocate new tail tile and increase the score

        bool loop = false;
        do {   // Generate new fruit positions while it is intersecting with something
            loop = false; // Sets it to false every loop

            fruit.newFruitPos(); // Generate new fruit position

            if(snake.head == fruit.fruitPos) // Pos of head equal to pos of fruit
                loop = true; // Continue looping

            else
            {
                for (int i = 0; i < snake.tailSize && !loop; i++)
                {
                    if(snake.tail[i] == fruit.fruitPos) // Pos of tail equal to pos of fruit
                        loop = true; // Continue looping
                }
            }
        } while(loop && snake.tailSize < _dimensions.x * _dimensions.y - 1); // If unique position is impossible, prevent the infinite cycle
    }
    
    if(snake.tailSize >= _dimensions.x * _dimensions.y - 1)
        gameWon = true; // Win if the whole play area is your snake

    snake.oldHead = snake.head; // Assign the current head to the old head
}

void SnakeGame::input() // Get input
{
    char input = getch(); // Get input
    switch (input) // Assign the corresponding direction to the snake
    {
    case 'a':
    case 'A':
        snake.direction = Direction::Left;
        break;
    case 'w':
    case 'W':
        snake.direction = Direction::Up;
        break;
    case 's':
    case 'S':
        snake.direction = Direction::Down;
        break;
    case 'd':
    case 'D':
        snake.direction = Direction::Right;
        break;
    default:
        break;
    }
}