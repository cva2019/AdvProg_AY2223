// UPDATE THIS FILE

#include <vector>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include "Game.h"

using namespace std;



// set some attributes as default value
// DO NOT CHANGE THIS CONSTRUCTOR
Game::Game(int _width, int _height)
    : width(_width), height(_height), // play screen 
	  squares(_height, vector<CellType>(_width, CELL_EMPTY)), // cell coordinates
      snake(*this, Position(_width/2, _height/2)),  // init snake positin in middle of play screen
      currentDirection(Direction::RIGHT),
      status(GAME_RUNNING),
      score(0)
{
	// add new cheery in game initiation
	addCherry();
}

Game::~Game()
{
    //dtor
}



/*** 
 * PLEASE UPDATE THIS METHOD
 * 
 * When snake moves to a position,
 * if position belongs to BOARD or SNAKE body, status is GAME_OVER
 * if position is having CHERRY :
 * 			- score schoule be increased
 * 			- snake should eat cherry
 * 			- a new cherry should be randomly added
 * otherwise, this position should be assigned as cell of snake 
 *
 * Args:
 * 		pos (Position): position where the snake will move
 * 
 * Returns:
 * 		// none
 * 
***/

void Game::snakeMoveTo(Position pos) {
	switch( getCellType( pos ) )
	{
        case CELL_OFF_BOARD:
        status = GAME_OVER;
        break;

        case CELL_SNAKE:
        status = GAME_OVER;
        break;

        case CELL_CHERRY:
        score += 1;
        snake.eatCherry();
        addCherry();
        break;

        case CELL_EMPTY:
        setCellType( pos, CELL_SNAKE );
        break;
	}
	//  START CODE HERE
	//
	//
	//
	//
	// END CODE HERE
}


/***
 * PLEASE UPDATE THIS METHOD
 * 
 * When all snake body leave a cell, set it as CELL_EMPTY
 * Args:
 * 		position (Position): position where snake will leave
 * Returns:
 * 		// none
 * 
 ***/
void Game::snakeLeave(Position position)
{
	setCellType( position, CELL_EMPTY );
	// Suggestion: use setCellType() method in Game class
	// START CODE HERE
	//  
	//
	//
	// END CODE HERE
}


// DO NOT change this method
void Game::processUserInput(Direction direction)
{
    inputQueue.push(direction);
}


/***
 * PLEASE REPLACE LINES MARKED WITH '// YOUR CODE HERE'
 * 
 * check whether the snake can move to the intended direction with the currect direction.
 * If current direction is UP or DOWN, the next direction should not be UP or DOWN
 * if current diection is LEFT or RIGHT, the next direction should not be LEFT or RIGHT
 * 
 * Args:
 * 		current (Direction): current direction of the snake
 * 		next (Direction): the intened direction that snake will move
 * Returns:
 * 		bool: whether the snake can ben changed the direction
 * 
 ***/
bool Game::canChange(Direction current, Direction next) const {
	if (current == UP || current == DOWN)
    {
        if (next == UP || next == DOWN) { return 0; }
        else return 1;
    }
    else
    {
        if (next == LEFT || next == RIGHT) { return 0; }
        else return 1;
    }
}



void Game::nextStep()
{
	while (!inputQueue.empty()) {
		// get the input direction from input queue
        Direction next= inputQueue.front();  // YOUR CODE HERE
         inputQueue.pop();
		// remove the front of input queue
        // YOUR CODE HERE

		// check if snake can move to the next direction, set current direction as next
        if (canChange(currentDirection, next)) {
			    currentDirection = next;
        	// YOUR CODE HERE
        	break;
		}
    }

    snake.move(currentDirection);
}


/***
 * PLEASE REPLACE LINES MARKED WITH '// YOUR CODE HERE'
 * 
 * When snake have already eaten a cherry, please add new cherry inside the play screen with random position
 * 
 * Args:
 * 		// none
 * Returns:
 * 		// none
 * 
 ***/

void Game::addCherry()
{
    do {
		// init a random position inside the play screen (width, height)
		// Suggestion: use rand() function

        Position randomPos(rand() % width, rand() % height); // YOUR CODE HERE

		// check if the randomPos is EMPTY
        if (getCellType(randomPos) == CELL_EMPTY) {
            cherryPosition = randomPos;
			setCellType(randomPos, CELL_CHERRY);

        	// assign the cherry position as randomPos, and set randomPos type as CELL_CHERRY

			// YOUR CODE HERE
			// YOUR CODE HERE

       		break;
        }
    } while (true);
}


/***
 * PLEASE UPDATE THIS METHOD
 * 
 * set cell of a position as intended type.
 * 
 * Args:
 * 		pos (Position): a chosen position
 * 		cellType (CellType): cell type of pos
 * Returns:
 * 		// none
 * 
 ***/
void Game::setCellType(Position pos, CellType cellType) 
{
	if(pos.isInsideBox(0, 0, width, height)) squares[pos.y][pos.x] = cellType;
	// if position is inside the play screen (width, height), set to the cellType.
	// Otherwise, do nothing
	// Suggestion: use pos.isInsideBox(...) in Position class
	//
	// START CODE HERE
	//  
	// END CODE HERE
}



// DO NOT change this method
CellType Game::getCellType(Position pos) const
{
	return pos.isInsideBox(0, 0, width, height) ? squares[pos.y][pos.x] : CELL_OFF_BOARD;
}

// DO NOT change this method
vector<Position> Game::getSnakePositions() const
{
    return snake.getPositions();
}

// DO NOT change this method
GameStatus Game::getGameStatus(){
	return status;
}

// DO NOT change this method
int Game::getWidth(){
	return width;
}

// DO NOT change this method
int Game::getHeight(){
	return height;
}

// DO NOT change this method
Snake Game::getSnake(){
	return snake;
}

